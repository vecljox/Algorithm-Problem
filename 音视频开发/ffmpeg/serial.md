PacketQueue 跟 FrameQueue 都是缓存队列

serial(序列号) 主要是给 快进快退 这个功能准备的。如果不能快进快退，那其实就不需要序列号。

只要解复用线程不断读取 AVPacket 放进去 PacketQueue 队列，解码线程不断从 PacketQueue 取数据来解码放进去 FrameQueue，最后有播放线程来取 FrameQueue 的数据取播放就行。

![image](https://github.com/user-attachments/assets/562d0930-f879-48b5-9913-6462e2e3bac6)

当进行快进、后退或者跳转时，serial会加1，导致一系列的连环反应
1. 从PacketQueue取出来的MyAVPacketList 的 serial如果不是最新的，会被丢弃掉。
2. 只要本次解码的 AVPacket 的序列号跟上一次用的 AVPacket 的序列号不一样，立即刷新解码器缓存。
3. 还有一个被连环影响的地方就是 读取 FrameQueue 的逻辑，FrameQueue 跟 PakcetQueue 不太一样，FrameQueue 本身是没有序列号的，只是它队列里面的 struct Frame 有 序列号，所以也会受到影响，
![image](https://github.com/user-attachments/assets/4fb696d8-7249-481c-a48c-ebd61a2dddd6)
