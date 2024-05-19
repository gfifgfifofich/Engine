#include "engine/Components/Redactor.h"


class CustomNode : public Object
{
public:
    
    CustomNode()
    {
	    type = 8;
	    Name = "Abobus";
	    ObjectPreconstructor();

    }

    virtual void OnResize(glm::vec2 prevdif,glm::vec2 mp, glm::vec2 prevmp) override
    {
        Scale -= prevdif;
        Scale += mp-prevmp;
    }
    

};


void PreReady()
{
    NodeConstructors.insert({8,[](){ return (Node*)new CustomNode();}});
    NodeConstructorNames.insert({8,"Customstussdsdsd"});
}

void Ready()
{

}

void Process(float dt)
{

}

void Destroy()
{

}