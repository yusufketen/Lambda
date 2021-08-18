#include <Lambda.h>

#include "EditorLayer.h"

namespace Lambda {

	class LambdaEditor : public Application
	{
	public:
		LambdaEditor()
			: Application("Lambda Editor")
		{
			PushLayer(new EditorLayer());
		}

		~LambdaEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new LambdaEditor();
	}

}