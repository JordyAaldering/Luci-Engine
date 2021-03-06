#pragma once

#include "Luci/Core/Core.h"
#include "Luci/Renderer/Texture.h"

#include <glm/glm.hpp>

namespace Luci {

	class SubTexture2D {
	public:
		SubTexture2D(const Ref<Texture2D>& texture, const glm::vec2& min, const glm::vec2& max);
		~SubTexture2D() = default;

		static Ref<SubTexture2D> CreateFromCoords(const Ref<Texture2D>& texture, const glm::vec2& coords, const glm::vec2& cellSize, const glm::vec2& spriteSize = { 1.0f, 1.0f });

		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const glm::vec2* GetTexCoords() const { return m_TexCoords; }

	private:
		Ref<Texture2D> m_Texture;
		glm::vec2 m_TexCoords[4];
	};

}
