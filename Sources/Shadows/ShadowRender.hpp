#pragma once

#include <vector>
#include "Scenes/Component.hpp"
#include "Renderer/Handlers/DescriptorsHandler.hpp"
#include "Renderer/Handlers/UniformHandler.hpp"
#include "Renderer/Pipelines/Pipeline.hpp"

namespace acid
{
	/// <summary>
	/// This component is used to render a entity as a shadow.
	/// </summary>
	class ACID_EXPORT ShadowRender :
		public Component
	{
	private:
		DescriptorsHandler m_descriptorSet;
		UniformHandler m_uniformObject;
	public:
		ShadowRender();

		void Start() override;

		void Update() override;

		void Decode(const Metadata &metadata) override;

		void Encode(Metadata &metadata) const override;

		bool CmdRender(const CommandBuffer &commandBuffer, const Pipeline &pipeline, UniformHandler &uniformScene);
	};
}
