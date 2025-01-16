# RTMP Chunk Stream 
允许 RTMP 在单一的底层 TCP 连接上传输多个独立的流数据（例如音频流、视频流、控制命令等），这些数据被划分为小块（chunks）进行传输。  
这种设计可以大幅提高数据传输效率，因为它允许音频、视频和控制信令共享一个 TCP 连接而无需额外的连接。
## Chunking
- 在握手之后，连接会对一个或多个块流进行多路复用。每个块流携带来自一个消息流的某种类型的消息。
- 每个创建的块都有一个唯一的 ID，称为块流 ID。
- 块通过网络传输。在传输过程中，每个块必须在下一个块之前完全发送。
- 在接收端，块根据块流 ID 被组装成消息。
- 块大小在每个方向上独立维护。
  
**分块允许在高级协议中将大消息拆分为更小的消息，例如，防止大低优先级消息（如视频）阻塞较小的高优先级消息（如音频或控制）。**  
**分块还允许以较少的开销发送小消息，因为块头包含了信息的压缩表示，而这些信息本来需要包含在消息本身中。**

### Chunk Format
![image](https://github.com/user-attachments/assets/970d2b84-76a5-488a-a33d-449ec083c9d4)
- #### Basic Header (1 to 3 bytes): 该字段编码了块流 ID 和块类型。块类型标识 ’chunk message header’ 使用的四种格式之一。基本头的长度完全取决于块流 ID，块流 ID 是一个可变长度字段。
  Basic Header分别有1,2,3字节3种版本，块类型由下图fmt字段表示,块基本头中的位 0-5（最低有效位）表示块流 ID。
---
  - ![image](https://github.com/user-attachments/assets/29431a1f-f4b9-4b63-8acd-ad914d25807a)  
    块流 ID 2-63 可以在该字段的 1 字节版本中编码。
---
  - ![image](https://github.com/user-attachments/assets/8048d388-87cd-4b66-9ea4-1becd7e7d8cf)  
    块流 ID 64-319 可以在头部的 2 字节形式中编码。ID 计算为（第二个字节 + 64）。
---
  - ![image](https://github.com/user-attachments/assets/9de6f795-b631-4e65-a8ec-6da934188ff5)  
    块流 ID 64-65599 可以在该字段的 3 字节版本中编码。ID 的计算方法是 ((第三字节) * 256 + (第二字节) + 64)。
---
  
