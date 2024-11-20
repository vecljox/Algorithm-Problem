[白皮书](https://bford.info/pub/net/p2pnat/)

***

## NAT类型

### Full Cone NAT（全锥型 NAT）
一旦内部主机建立了一个映射，任何外部主机都可以向该映射端口发送数据包，穿透成功率最高。

### Restricted Cone NAT（限制锥型 NAT）
一旦内部主机通过NAT发送数据包到外部主机，NAT会创建端口映射。之后，只有**这个外部主机的IP地址**可以向这个映射端口发送数据包，其他IP的数据包会被丢弃。

### Port-Restricted Cone NAT（端口限制锥型 NAT）
和`Restricted Cone NAT`类似，但要求外部主机的**IP地址**和**端口号**都必须匹配映射条件

### Symmetric NAT（对称型 NAT）
**不提供一致的端点转换**，每个目的地址都使用不同的映射端口，几乎无法通过常规方式实现穿透，成功率最低。

***
## 影响UDP穿透率的因素
### NAT类型
NAT 类型直接决定了 UDP 穿透的难度，不同 NAT 类型对 UDP 穿透支持的能力不同
### NAT超时策略
NAT的映射表会定期清理未使用的条目：
+ 如果 NAT 映射超时时间较短，UDP 穿透会失败，尤其是在 P2P 连接建立过程中。
+ 解决方案：定期发送UDP包保持会话活跃。
### 网络拓扑复杂性
多层 NAT（如双路由器）：两层或更多 NAT 会显著降低穿透率，需要NAT能够`hairpin translation`**(回环转换)**。
