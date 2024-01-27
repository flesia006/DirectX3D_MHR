#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
    trees.reserve(COUNT);

    FOR(COUNT)
    {
        //기준 크기 벡터2로 만들기
        Vector2 size;
        size.x = Random(2.0f, 10.0f);
        size.y = Random(2.0f, 10.0f);

        Quad* tree = new Quad(size); // 도출된 크기로 흰 사각형부터 만들기
        tree->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Tree.png"); //디퓨즈맵 입히기
        
        //위치 랜덤으로 바꾸기
        tree->Pos().x = Random(0.0f, 50.0f);
        tree->Pos().z = Random(0.0f, 50.0f);
        tree->Pos().y = 0;

        trees.push_back(tree);

        //캔버싱용 트랜스폼과 벡터 준비
        Transform* transform = new Transform();
        transform->Pos() = tree->Pos();
        origins.push_back(transform);
    }
    FOR(2) blendState[i] = new BlendState();
    blendState[1]->AlphaToCoverage(true);
}

BillboardScene::~BillboardScene()
{
    for (Quad* tree : trees)
        delete tree;
}

void BillboardScene::Update()
{
    //이미지를 빌보드로 적용하는 방법

    //....중에서, 직접 제어 방법

    //벡터를 이용한 텍스처 방향 제어
    //for (Quad* tree : trees)
    //{
    //    //아무튼 텍스처가 카메라만 보면 그만
    //    Vector3 dir = tree->Pos() - CAM->Pos(); //카메라가 나무를 보게 만들고
    //    tree->Rot().y = atan2(dir.x, dir.z); //나무에 역탄젠트 적용. 평면상의 xy = DX벡터의 xz
    //    tree->UpdateWorld(); //방향이 바뀐 나무의 사각형 정점 업데이트
    //}

    ////텍스처와 카메라 방향 동기화
    //for (Quad* tree : trees)
    //{
    //    tree->Rot().x = CAM->Rot().x;
    //    tree->Rot().y = CAM->Rot().y;
    //    tree->UpdateWorld();
    //}

    //캔버싱
    for (Quad* tree : trees)
    {
        //나무와 순번이 일치하는 트랜스폼(원점) 찾기
        int index = find(trees.begin(), trees.end(), tree) - trees.begin();
        //find : 벡터 내장 함수. 매개변수로 찾을 범위와 대상을 주면 대상 위치를 가진 반복자 반환
        //반복자 계산 특징 : 반복자끼리는 숫자처럼 계산 가능. 반복자 자신은 누적 가능 (iter++)
        // -> find의 결과에 벡터의 begin()을 빼면 마치 순번에서 0을 뺀 것처럼 숫자 도출 가능
        Transform* point = origins.at(index); //나무의 본래 위치가 기록된 트랜스폼

        Vector3 pos = point->Pos();
        tree->Pos() = CAM->WorldToScreen(pos);
        float scale = 100 / (tree->Pos() - CAM->Pos()).Length();
        scale = Clamp(10.0f, 10.0f, scale);
        tree->Scale() = { scale, scale, scale };
        tree->UpdateWorld();
    }
}

void BillboardScene::PreRender()
{
}

void BillboardScene::Render()
{
    //for (Quad* tree : trees)
    //    tree->Render();
}

void BillboardScene::PostRender()
{
    //blendState[1]->SetState();
    for (Quad* tree : trees)
        tree->Render();
    //blendState[0]->SetState();
}

void BillboardScene::GUIRender()
{
}
