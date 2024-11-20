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


