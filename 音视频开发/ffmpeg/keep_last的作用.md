```c
typedef struct FrameQueue {
	Frame queue[FRAME_QUEUE_SIZE];
	int rindex;
	int windex;
	int size;
	int max_size;

	int keep_last;

	int rindex_shown;
	SDL_mutex* mutex;
	SDL_cond* cond;
	PacketQueue* pktq;
} FrameQueue;
```
ffplay的FrameQueue结构体中有个字段keep_last，表示**最近播放一帧是否保存在队列里面不销毁**


```c
static void frame_queue_next(FrameQueue* f)
{
	// 如果设置了keep_last标志并且rindex_shown为0，则设置rindex_shown为1并返回。
	// 这意味着队列中最后一个帧保持不变。
	if (f->keep_last && !f->rindex_shown) {
		f->rindex_shown = 1;
		return;
	}

	// 释放当前帧的资源，减少其引用计数。
	frame_queue_unref_item(&f->queue[f->rindex]);

	// 移动到帧队列中的下一个位置。
	if (++f->rindex == f->max_size)
		f->rindex = 0;
  ...
}
```
对于 FrameQueue 队列， peek + next 是分开操作的

frame_queue_next作用是释放 AVFrame 的引用内存，然后把**读索引+1**

但是 frame_queue_next() 一开始有一个 if 判断，对于音频/视频流，keep_last 一开始是 1，而 rindex 是 0，所以就会把 rindex_shown 置为 1 了，然后 return，直接返回了。

可以这么理解，**rindex是用来读取上一帧已经播放的AVFrame的，rindex + rindex_shown用来读取下一个准备播放的 AVFrame 的**
```c
static Frame* frame_queue_peek_last(FrameQueue* f)
{
	return &f->queue[f->rindex];
}

static Frame* frame_queue_peek(FrameQueue* f)
{
	return &f->queue[(f->rindex + f->rindex_shown) % f->max_size];
}

所以，keep_last 是为了控制 rindex_shown 变成 1 的，而 rindex_shown 是为了实现保留上一帧在队列，还能顺利往前继续读数据的功能。
```
使用keep_last 选项可以在视频播放结束后，最后一帧仍然显示在屏幕上，用户可以清晰地看到最后的场景，而不是看到黑屏或默认背景，增强用户体验。
