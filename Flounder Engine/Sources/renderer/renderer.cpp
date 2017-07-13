#include "renderer.h"

namespace flounder {
	renderer::renderer()
		: imodule()
	{
		m_renderermaster = NULL;
	}

	renderer::~renderer()
	{
		delete m_renderermaster;
	}

	void renderer::loadRendererMaster(irenderermaster *renderermaster)
	{
		m_renderermaster = renderermaster;
	}

	void renderer::init()
	{
	}

	void renderer::update()
	{
		if (m_renderermaster != NULL)
		{
			m_renderermaster->render();
		}
	}

	void renderer::prepareNewRenderParse(colour *colour)
	{
		prepareNewRenderParse(colour->r, colour->g, colour->b);
	}

	void renderer::prepareNewRenderParse(const float r, const float g, const float b)
	{
		glClearColor(r, g, b, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		disableBlending();
		cullBackFaces(true);
		enableDepthTesting();
	}

	void renderer::cullBackFaces(const bool cull)
	{
		if (cull && !m_cullingBackFace) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			m_cullingBackFace = true;
		}
		else if (!cull && m_cullingBackFace) {
			glDisable(GL_CULL_FACE);
			m_cullingBackFace = false;
		}
	}

	void renderer::enableDepthTesting()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void renderer::disableDepthTesting()
	{
		glDisable(GL_DEPTH_TEST);
	}

	void renderer::depthMask(const bool depthMask)
	{
		m_depthMask = depthMask;
		glDepthMask(depthMask);
	}

	bool renderer::isInWireframe()
	{
		return m_inWireframe;
	}

	void renderer::goWireframe(const bool goWireframe)
	{
		if (goWireframe && !m_inWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			m_inWireframe = true;
		}
		else if (!goWireframe && m_inWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			m_inWireframe = false;
		}
	}

	void renderer::enableAlphaBlending()
	{
		if (!m_isAlphaBlending)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			m_isAlphaBlending = true;
			m_additiveBlending = false;
		}
	}

	void renderer::enableAdditiveBlending()
	{
		if (!m_additiveBlending)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			m_additiveBlending = true;
			m_isAlphaBlending = false;
		}
	}

	void renderer::disableBlending()
	{
		if (m_isAlphaBlending || m_additiveBlending)
		{
			glDisable(GL_BLEND);
			m_isAlphaBlending = false;
			m_additiveBlending = false;
		}
	}

	void renderer::antialias(const bool enable)
	{
		if (enable && !m_antialiasing)
		{
			glEnable(GL_MULTISAMPLE);
			m_antialiasing = true;
		}
		else if (!enable && m_antialiasing)
		{
			glDisable(GL_MULTISAMPLE);
			m_antialiasing = false;
		}
	}

	void renderer::bindVAO(const int vaoID, const int n_args, ...)
	{
		glBindVertexArray(vaoID);

		va_list ap;
		va_start(ap, n_args);

		for (unsigned int i = 0; i < n_args; i++)
		{
			int attribute = va_arg(ap, int);
			glEnableVertexAttribArray(attribute);
		}

		va_end(ap);
	}

	void renderer::unbindVAO(const int n_args, ...)
	{
		va_list ap;
		va_start(ap, n_args);

		for (unsigned int i = 0; i < n_args; i++)
		{
			int attribute = va_arg(ap, int);
			glDisableVertexAttribArray(attribute);
		}

		va_end(ap);

		glBindVertexArray(0);
	}

	void renderer::scissor(const int x, const int y, const int width, const int height)
	{
		glScissor(x, y, width, height);
	}

	void renderer::bindTexture(texture *texture, const int bankID)
	{
		if (texture == NULL || texture->getTextureID() == -1) 
		{
			return;
		}

		glActiveTexture(GL_TEXTURE0 + bankID);
		glBindTexture(texture->getGlType(), texture->getTextureID());
	}

	void renderer::bindTexture(const int textureID, const int glTarget, const int bankID)
	{
		if (textureID == -1) 
		{
			return;
		}

		glActiveTexture(GL_TEXTURE0 + bankID);
		glBindTexture(glTarget, textureID);
	}

	void renderer::bindTextureLOD(const int textureID, const int lodBias, const int bankID)
	{
		if (textureID == -1) 
		{
			return;
		}

		glActiveTexture(GL_TEXTURE0 + bankID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, lodBias);
		glActiveTexture(0);
	}

	void renderer::renderArrays(const GLenum glMode, const GLsizei glLength)
	{
		glDrawArrays(glMode, 0, glLength);
	}

	void renderer::renderElements(const GLenum glMode, const GLenum glType, const GLsizei glLength)
	{
		glDrawElements(glMode, glLength, glType, 0);
	}

	void renderer::renderInstanced(const GLenum glMode, const GLsizei glLength, const GLsizei glPrimCount)
	{
		glDrawArraysInstanced(glMode, 0, glLength, glPrimCount);
		// glDrawArraysInstancedARB(glMode, 0, glLength, glPrimCount);
	}
}
