#ifndef DATA_PARSE_H
#define DATA_PARSE_H

#define BUFFER_VAL_MAX 100  //一帧最大值
#define FRAME_NUM_MAX  100  //缓冲区最大帧数

//定义缓冲帧
class FrameBufferDef
{
public:
    char buff[BUFFER_VAL_MAX];
};

//定义解析器
class ParserDef
{
public:
    FrameBufferDef frameBuffers[FRAME_NUM_MAX];     //解析器缓冲
    bool isFrameBUffersEmpty;                       //缓冲区是否空
    bool isFrameBuffersFull;                        //缓冲区是否满
    int frameLength;                                //缓冲区帧数
    int addIdx;                                     //添加索引
    int getIdx;                                     //取出索引


    void parsingHandle();

private:
    int getFrameLength();
    bool frameParse();
};

extern ParserDef parser;

#endif // DATA_PARSE_H
