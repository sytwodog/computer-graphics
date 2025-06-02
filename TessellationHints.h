#pragma once
#include "CGObject.h"
class TessellationHints :
    public CGObject
{
public:
    TessellationHints() { }
    TessellationHints(const TessellationHints& tess) :
        CGObject(tess),
        mDetailRatio(tess.mDetailRatio),
        mTargetSlices(tess.mTargetSlices),
        mTargetStacks(tess.mTargetStacks),
        mCreateFrontFace(tess.mCreateFrontFace),
        mCreateBackFace(tess.mCreateBackFace),
        mCreateNormals(tess.mCreateNormals),
        mCreateTextureCoords(tess.mCreateTextureCoords),
        mCreateTop(tess.mCreateTop),
        mCreateBody(tess.mCreateBody),
        mCreateBottom(tess.mCreateBottom) {
    }
    ~TessellationHints() {}
    inline void setDetailRatio(float ratio) { mDetailRatio = ratio; }
    inline float detailRatio() const { return mDetailRatio; }
    inline void setTargetSlices(unsigned int target) { mTargetSlices = target; }
    inline unsigned int targetSlices() const { return mTargetSlices; }
    inline void setTargetStacks(unsigned int target) { mTargetStacks = target; }
    inline unsigned int targetStacks() const { return mTargetStacks; }
    inline void setCreateFrontFace(bool on) { mCreateFrontFace = on; }
    inline bool createFrontFace() const { return mCreateFrontFace; }
    inline void setCreateBackFace(bool on) { mCreateBackFace = on; }
    inline bool createBackFace() const { return mCreateBackFace; }
    inline void setCreateNormals(bool on) { mCreateNormals = on; }
    inline bool createNormals() const { return mCreateNormals; }
    inline void setCreateTextureCoords(bool on) { mCreateTextureCoords = on; }
    inline bool createTextureCoords() const { return mCreateTextureCoords; }
    inline void setCreateTop(bool on) { mCreateTop = on; }
    inline bool createTop() const { return mCreateTop; }
    inline void setCreateBody(bool on) { mCreateBody = on; }
    inline bool createBody() const { return mCreateBody; }
    inline void setCreateBottom(bool on) { mCreateBottom = on; }
    inline bool createBottom() const { return mCreateBottom; }
protected:
    float mDetailRatio = 1.0f; //��ϸ�̶ȣ���ϸ������
    unsigned int mTargetSlices = 40; //��Z���ϸ��������ͬ��״���ò�ͬ��
    unsigned int mTargetStacks = 20; //��Z���ϸ��������ͬ��״���ò�ͬ��
    bool mCreateFrontFace = true; //����������
    bool mCreateBackFace = false; //���ɱ�����
    bool mCreateNormals = true; //���ɷ�����
    bool mCreateTextureCoords = true; //������������
    bool mCreateTop = true; //���ɶ���
    bool mCreateBody = true; //���ɲ��� 
    bool mCreateBottom = true; //���ɵ���
};


