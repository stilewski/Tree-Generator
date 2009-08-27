#include "Scene.h"


CScene::CScene()
{
    m_Lighting = false;
    m_Texturing = false;
}

CScene::~CScene()
{
}

void CScene::ChangeLighting( void )
{
    m_Lighting = !m_Lighting;
}

void CScene::ChangeTexturing( void )
{
    m_Texturing = !m_Texturing;
}

bool CScene::IsLighting( void )
{
    return m_Lighting;
}

bool CScene::IsTexturing( void )
{
    return m_Texturing;
}


