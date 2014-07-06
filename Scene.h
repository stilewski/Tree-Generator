#ifndef SCENE_H
#define SCENE_H

#include "Singleton.h"
#include "common.h"

class CScene : public cSingleton< CScene >
{
    public:
    CScene();
    ~CScene();

    void ChangeLighting( void );
    void ChangeTexturing( void );
    bool IsLighting( void );
    bool IsTexturing( void );

    private:
    bool m_Lighting;
    bool m_Texturing;
};

#define scene CScene::GetInstance()

#endif // SCENE_H
