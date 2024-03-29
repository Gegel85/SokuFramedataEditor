//
// Created by andgel on 18/09/2021
//

#include <fstream>
#include "FrameData.hpp"
#include "Game.hpp"
#include "Utils.hpp"

namespace SpiralOfFate
{
	std::map<unsigned, std::vector<std::vector<FrameData>>> FrameData::loadSchema(const std::string &chr, const ShadyCore::Schema &schema, const ShadyCore::Palette &palette, const std::string &palName)
	{
		std::map<unsigned int, std::vector<std::vector<FrameData>>> result;
		std::vector<ShadyCore::Schema::Clone *> objects;

		for (auto &sequ : schema.objects) {
			if (sequ->getType() == 7)
				objects.push_back(reinterpret_cast<ShadyCore::Schema::Clone *>(sequ));
			else if (sequ->getType() == 9) {
				result[sequ->getId()].emplace_back();

				auto &sequence = *reinterpret_cast<ShadyCore::Schema::Sequence *>(sequ);
				auto &arr = result[sequ->getId()].back();

				arr.reserve(sequence.frames.size());
				for (auto move : sequence.frames) {
#ifdef _DEBUG
					assert(dynamic_cast<ShadyCore::Schema::Sequence::MoveFrame *>(move));
#endif
					arr.emplace_back(chr, schema, sequence, *reinterpret_cast<ShadyCore::Schema::Sequence::MoveFrame *>(move), palette, palName);
				}
			} else
				throw std::invalid_argument("Found unknown object id " + std::to_string(sequ->getType()) + " in schema");
		}
		for (auto &object : objects) {
			game->logger.info(std::to_string(object->getId()) + " is a clone of " + std::to_string(object->targetId));

			auto r = result.emplace(object->getId(), result[object->targetId]);

			if (!r.second)
				Utils::dispMsg("Invalid clone", "Action " + std::to_string(object->getId()) + " already exists but is trying to be cloned (from " + std::to_string(object->targetId) + ").", MB_ICONERROR);
			//TODO: Store clone and notify user
			//else
			//	r.first->clone = object->targetId;
		}
		if (result.begin() == result.end())
			throw std::invalid_argument("Schema is empty!");
		return result;
	}

	FrameData::FrameData(const std::string &chr, const ShadyCore::Schema &schema, ShadyCore::Schema::Sequence &parent, ShadyCore::Schema::Sequence::MoveFrame &frame, const ShadyCore::Palette &palette, const std::string &palName) :
		_pal(palName),
		_character(chr),
		_palette(&palette),
		_schema(&schema),
		parent(&parent),
		frame(&frame)
	{
		Vector2u textureSize;

		for (auto &box : this->frame->hBoxes)
			if (box.up > box.down) {
				auto down = box.up;

				box.up = box.down;
				box.down = down;
			}
		for (auto &box : this->frame->aBoxes)
			if (box.up > box.down) {
				auto down = box.up;

				box.up = box.down;
				box.down = down;
			}
		try {
			this->textureHandle = game->textureMgr.load(game->package, *this->_palette, this->_pal, "data/character/" + this->_character + "/" + this->_schema->images.at(this->frame->imageIndex).name, &textureSize);
		} catch (std::exception &e) {
			game->logger.error("Error loading texture: " + std::string(e.what()) + "\n");
		}
		if (this->frame->traits.onHitSfx) {
			char buffer[4];

			sprintf(buffer, "%03d", this->frame->traits.onHitSfx);
			this->hitSoundHandle = game->soundMgr.load(game->package, "data/se/" + std::string(buffer) + ".cv3");
		}
		if (this->frame->cBoxes.size() > 1)
			throw std::runtime_error("FrameData::FrameData: More than one collision box is not supported");
		for (auto &box : this->frame->cBoxes)
			if (box.extra)
				throw std::runtime_error("FrameData::FrameData: Extra collision box is not supported");
		for (auto &box : this->frame->aBoxes)
			if (box.extra)
				throw std::runtime_error("FrameData::FrameData: Extra attack box is not supported");
		for (auto &box : this->frame->hBoxes)
			if (box.extra)
				throw std::runtime_error("FrameData::FrameData: Extra hit box is not supported");
	}

	FrameData::~FrameData()
	{
		if (!this->_slave)
			game->textureMgr.remove(this->textureHandle);
	}

	FrameData::FrameData(const FrameData &other) :
		_pal(other._pal),
		_character(other._character),
		_palette(other._palette),
		_schema(other._schema),
		parent(other.parent),
		frame(other.frame)
	{
		this->textureHandle = other.textureHandle;
		this->hitSoundHandle = other.hitSoundHandle;
		if (!this->_slave) {
			game->textureMgr.addRef(this->textureHandle);
			game->soundMgr.addRef(this->hitSoundHandle);
		}
	}

	FrameData::FrameData(const FrameData &other, ShadyCore::Schema::Sequence::MoveFrame &frame) :
		FrameData(other)
	{
		this->frame = &frame;
	}

	void FrameData::reloadTexture()
	{
		my_assert(!this->_slave);
		this->needReload = false;
		game->textureMgr.remove(this->textureHandle);
		try {
			this->textureHandle = game->textureMgr.load(game->package, *this->_palette, this->_pal, "data/character/" + this->_character + "/" + this->_schema->images.at(this->frame->imageIndex).name);
		} catch (std::exception &e) {
			game->logger.error("Error loading texture: " + std::string(e.what()) + "\n");
		}
	}

	void FrameData::reloadSound()
	{
		my_assert(!this->_slave);
		game->soundMgr.remove(this->hitSoundHandle);
		this->hitSoundHandle = 0;
		if (this->frame->traits.onHitSfx) {
			char buffer[4];

			sprintf(buffer, "%03d", this->frame->traits.onHitSfx);
			this->hitSoundHandle = game->soundMgr.load(game->package, "data/se/" + std::string(buffer) + ".cv0");
		}
	}

	void FrameData::setSlave(bool slave)
	{
		if (!slave && this->_slave) {
			game->textureMgr.addRef(this->textureHandle);
			game->soundMgr.addRef(this->hitSoundHandle);
		} else if (slave && !this->_slave) {
			game->textureMgr.remove(this->textureHandle);
			game->soundMgr.remove(this->hitSoundHandle);
		}
		this->_slave = slave;
	}

	void FrameData::setPalette(const ShadyCore::Palette &palette, const std::string &name)
	{
		this->needReload = !this->_slave;
		this->_pal = name;
		this->_palette = &palette;
	}


	FrameData &FrameData::operator=(const FrameData &other)
	{
		this->_pal = other._pal;
		this->_character = other._character;
		this->_palette = other._palette;
		if (!this->_slave) {
			game->textureMgr.remove(this->textureHandle);
			game->soundMgr.remove(this->hitSoundHandle);
			game->textureMgr.addRef(other.textureHandle);
			game->soundMgr.addRef(other.hitSoundHandle);
		}
		this->textureHandle = other.textureHandle;
		this->hitSoundHandle = other.hitSoundHandle;
		this->needReload = other.needReload;
		this->_schema = other._schema;
		this->frame = other.frame;
		return *this;
	}

	FrameData &FrameData::operator=(FrameData &&other) noexcept
	{
		this->_pal = other._pal;
		this->_character = other._character;
		this->_palette = other._palette;
		if (!this->_slave) {
			game->textureMgr.remove(this->textureHandle);
			game->soundMgr.remove(this->hitSoundHandle);
			game->textureMgr.addRef(other.textureHandle);
			game->soundMgr.addRef(other.hitSoundHandle);
		}
		this->textureHandle = other.textureHandle;
		this->hitSoundHandle = other.hitSoundHandle;
		this->needReload = other.needReload;
		this->_schema = other._schema;
		this->frame = other.frame;
		return *this;
	}

	Box::operator sf::IntRect() const noexcept
	{
		return {
			this->pos.x, this->pos.y,
			static_cast<int>(this->size.x), static_cast<int>(this->size.y)
		};
	}
}
