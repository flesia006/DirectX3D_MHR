#pragma once
class BillboardScene : public Scene
{
    //빌보드 : 간판, 특히 거리에 크게 세워두는 간판
    //        프로그래밍에서는 언제나 100% 출력되는 이미지 UI를 지칭 (2D)
    //        혹은 카메라의 방향, 위치에 상관없이 정면을 확인 가능한 이미지 출력을 지칭(3D)

private:
    UINT COUNT = 100;

public:
    BillboardScene();
    ~BillboardScene();

    virtual void Update() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void PostRender() override;
    virtual void GUIRender() override;

private:
    vector<Quad*> trees; //예시 이미지 = 나무

    // 빌보드 구현을 위한 방법
    // A : 벡터를 이용한 방향 제어 : 단순, 평면 표현 외에 완전한 고정이나 각도제어 등은 힘들다
    // B : 카메라와 방향 동기화    : 보이는 건 안정적, 카메라에 의존한다
    // C : 캔버싱                 : 표현의 결과가 안정적, 실제 월드와 투사 결과 위치가 꼭 같진 않다
    //                          //허공에 나무가 떠 있거나.. 나무가 있는 곳에 가도 거기에 실체가 있다는 보장은 없다
    //                          //순수하게 보이는 것만이 목적일 때 쓰면 좋다
    // D : ?????

    // C 방법을 위한 추가 변수
    vector<Transform*> origins; //나무 위치의 원점을 기록한 벡터
    BlendState* blendState[2];
};

