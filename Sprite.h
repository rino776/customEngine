#pragma once
#include "Component.h"
#include "Texture.h"
#include "GameObject.h"

//I think I want this to be solely used for UI stuff.
class Sprite :
    public Component {

public:
    Sprite(Texture* texture);
    Texture* texture;

    void Init() override;
    void Update() override;
    void Render() override;
    int getID() override;
    void setGameObject(void*) override;

protected:
    GameObject* Container;

private:
    unsigned int VAO, VBO, EBO;
    
};

