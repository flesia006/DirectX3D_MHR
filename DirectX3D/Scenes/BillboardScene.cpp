#include "Framework.h"
#include "BillboardScene.h"

BillboardScene::BillboardScene()
{
    trees.reserve(COUNT);

    FOR(COUNT)
    {
        //���� ũ�� ����2�� �����
        Vector2 size;
        size.x = Random(2.0f, 10.0f);
        size.y = Random(2.0f, 10.0f);

        Quad* tree = new Quad(size); // ����� ũ��� �� �簢������ �����
        tree->GetMaterial()->SetDiffuseMap(L"Textures/Landscape/Tree.png"); //��ǻ��� ������
        
        //��ġ �������� �ٲٱ�
        tree->Pos().x = Random(0.0f, 50.0f);
        tree->Pos().z = Random(0.0f, 50.0f);
        tree->Pos().y = 0;

        trees.push_back(tree);

        //ĵ���̿� Ʈ�������� ���� �غ�
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
    //�̹����� ������� �����ϴ� ���

    //....�߿���, ���� ���� ���

    //���͸� �̿��� �ؽ�ó ���� ����
    //for (Quad* tree : trees)
    //{
    //    //�ƹ�ư �ؽ�ó�� ī�޶� ���� �׸�
    //    Vector3 dir = tree->Pos() - CAM->Pos(); //ī�޶� ������ ���� �����
    //    tree->Rot().y = atan2(dir.x, dir.z); //������ ��ź��Ʈ ����. ������ xy = DX������ xz
    //    tree->UpdateWorld(); //������ �ٲ� ������ �簢�� ���� ������Ʈ
    //}

    ////�ؽ�ó�� ī�޶� ���� ����ȭ
    //for (Quad* tree : trees)
    //{
    //    tree->Rot().x = CAM->Rot().x;
    //    tree->Rot().y = CAM->Rot().y;
    //    tree->UpdateWorld();
    //}

    //ĵ����
    for (Quad* tree : trees)
    {
        //������ ������ ��ġ�ϴ� Ʈ������(����) ã��
        int index = find(trees.begin(), trees.end(), tree) - trees.begin();
        //find : ���� ���� �Լ�. �Ű������� ã�� ������ ����� �ָ� ��� ��ġ�� ���� �ݺ��� ��ȯ
        //�ݺ��� ��� Ư¡ : �ݺ��ڳ����� ����ó�� ��� ����. �ݺ��� �ڽ��� ���� ���� (iter++)
        // -> find�� ����� ������ begin()�� ���� ��ġ �������� 0�� �� ��ó�� ���� ���� ����
        Transform* point = origins.at(index); //������ ���� ��ġ�� ��ϵ� Ʈ������

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
