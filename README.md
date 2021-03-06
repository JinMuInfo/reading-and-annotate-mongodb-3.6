# reading-and-annotate-mongodb-3.6

mongodb-3.6源码注释分析，持续更新

===================================     
### <<mongodb源码设计实现、性能优化、最佳运维实践>>
### <<千万级峰值tps/十万亿级数据量文档数据库内核研发及运维之路>>   
  * [百万级高并发mongodb集群性能数十倍提升优化实践(上篇)](https://my.oschina.net/u/4087916/blog/3141909)      
  * [百万级高并发mongodb集群性能数十倍提升优化实践(下篇)](https://my.oschina.net/u/4087916/blog/3155205)    
  * [Mongodb网络传输处理源码实现及性能调优-体验内核性能极致设计](https://my.oschina.net/u/4087916/blog/4295038)      
  * [常用高并发网络线程模型设计及mongodb线程模型优化实践(最全高并发网络IO线程模型设计及优化)](https://my.oschina.net/u/4087916/blog/4431422)  
  * [Mongodb集群搭建一篇就够了-复制集模式、分片模式、带认证、不带认证等(带详细步骤说明)](https://my.oschina.net/u/4087916/blog/4661542)      
  * [Mongodb特定场景性能数十倍提升优化实践(记一次mongodb核心集群雪崩故障)](https://blog.51cto.com/14951246)  
  * [mongodb内核源码设计实现、性能优化、最佳运维系列-mongodb网络传输层模块源码实现二](https://zhuanlan.zhihu.com/p/265701877)  
  * [为何需要对开源mongodb社区版本做二次开发，需要做哪些必备二次开发](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/development_mongodb.md)  
  * [对开源mongodb社区版本做二次开发收益列表](https://my.oschina.net/u/4087916/blog/3063529)  
  * [mongodb内核源码实现、性能调优、最佳运维实践系列-mongodb网络传输层模块源码实现二](https://my.oschina.net/u/4087916/blog/4674521)      
  * [mongodb内核源码实现、性能调优、最佳运维实践系列-mongodb网络传输层模块源码实现三](https://my.oschina.net/u/4087916/blog/4678616)    
  * [mongodb内核源码实现、性能调优、最佳运维实践系列-mongodb网络传输层模块源码实现四](https://my.oschina.net/u/4087916/blog/4685419)     
  
    
说明:  
===================================  
MongoDB是一个基于分布式文件存储的数据库。由C++语言编写。旨在为WEB应用提供可扩展的高性能数据存储解决方案。  
是一个介于关系数据库和非关系数据库之间的产品，是非关系数据库当中功能最丰富，最像关系数据库的。他支持的数据结构非常松散，是类似json的bson格式，因此可以存储比较复杂的数据类型。Mongo最大的特点是他支持的查询语言非常强大，其语法有点类似于面向对象的查询语言，几乎可以实现类似关系数据库单表查询的绝大部分功能，而且还支持对数据建立索引。  
  
源码中文已注释代码列表如下：
===================================   
#### boost-asio网络库/定时器源码实现注释(只注释mongodb相关实现的asio库代码)(100%注释):   
 *   [asio/include/asio/detail/impl/scheduler.ipp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/impl/scheduler.ipp) 
 *   [asio/include/asio/detail/impl/epoll_reactor.ipp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/impl/epoll_reactor.ipp) 
 *   [asio/include/asio/detail/scheduler.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/scheduler.hpp) 
 *   [asio/include/asio/detail/impl/scheduler.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/impl/scheduler.hpp) 
 *   [asio/include/asio/detail/timer_queue.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/timer_queue.hpp) 
 *   [asio/include/asio/detail/timer_queue_base.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/timer_queue_base.hpp) 
 *   [asio/include/asio/detail/timer_queue_set.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/timer_queue_set.hpp) 
 *   [asio/include/asio/detail/impl/timer_queue_set.ipp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/impl/timer_queue_set.ipp) 
 *   [asio/include/asio/detail/epoll_reactor.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/epoll_reactor.hpp) 
 *   [asio/include/asio/detail/impl/epoll_reactor.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/impl/epoll_reactor.hpp) 
 *   [asio/include/asio/impl/read.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/impl/read.hpp) 
 *   [asio/include/asio/impl/write.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/impl/write.hpp) 
 *   [asio/include/asio/basic_socket_acceptor.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation//asio/include/asio/basic_socket_acceptor.hpp) 
 *   [asio/include/asio/detail/reactive_socket_service.hpp)](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/reactive_socket_service.hpp) 
 *   [asio/include/asio/basic_socket_acceptor.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/basic_socket_acceptor.hpp) 
 *   [asio/include/asio/basic_stream_socket.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/basic_stream_socket.hpp) 
 *   [asio/include/asio/detail/reactive_socket_service_base.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/reactive_socket_service_base.hpp) 
 *   [asio/include/asio/detail/reactive_socket_recv_op.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/reactive_socket_recv_op.hpp) 
 *   [asio/include/asio/detail/reactor_op.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/reactor_op.hpp) 
 *   [asio/include/asio/detail/scheduler_operation.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/scheduler_operation.hpp) 
 *   [asio/include/asio/detail/deadline_timer_service.hpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/third_party/asio-chinese-annotation/asio/include/asio/detail/deadline_timer_service.hpp) 

#### mongodb网络传输模块(transport)处理实现(100%注释):     
###### transport_layer传输层子模块: 
 *   [transport_layer_asio.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/transport_layer_asio.h) 
 *   [transport_layer_asio.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/transport_layer_asio.cpp) 
 *   [transport_layer_manager.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/transport_layer_manager.h) 
 *   [transport_layer_manager.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/transport_layer_manager.cpp) 
 *   [transport_layer.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/transport_layer.h) 
###### Ticket数据收发回调处理子模块(100%注释): 
 *   [ticket_asio.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/ticket_asio.h) 
 *   [ticket_asio.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/ticket_asio.cpp) 
 *   [ticket_impl.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/ticket_impl.h) 
###### Session会话子模块(100%注释): 
 *   [session_asio.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/session_asio.h) 
 *   [session_asio.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/session_asio.cpp) 
 *   [session.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/session.h) 
###### service_state_machine状态机子模块(100%注释): 
 *   [service_state_machine.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_state_machine.h) 
 *   [service_state_machine.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_state_machine.cpp) 
###### service_executor服务运行(工作线程模型)子模块(100%注释): 
 *   [service_executor.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_executor.h) 
 *   [service_executor_adaptive.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_executor_adaptive.cpp) 
 *   [service_executor_adaptive.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_executor_adaptive.h) 
 *   [service_executor_synchronous.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_executor_synchronous.cpp) 
 *   [service_executor_synchronous.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_executor_synchronous.h) 
###### service_entry_point_impl服务入口子模块(100%注释): 
 *   [service_entry_point.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_entry_point.h) 
 *   [service_entry_point_impl.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_entry_point_impl.cpp) 
 *   [service_entry_point_impl.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_entry_point_impl.h) 
 *   [service_entry_point_utils.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_entry_point_utils.cpp) 
 *   [service_entry_point_utils.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/transport/service_entry_point_utils.h) 

#### message/DbMessage/OpMsgRequest协议处理(100%注释): 
 *   [message.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/util/net/message.h) 
 *   [message.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/util/net/message.cpp) 
 *   [dbmessage.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/dbmessage.h) 
 *   [dbmessage.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/dbmessage.cpp) 
 *   [factory.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/rpc/factory.cpp) 
 *   [factory.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/rpc/factory.h) 
 *   [op_msg.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/util/net/op_msg.cpp) 
 *   [op_msg.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/util/net/op_msg.h) 
 
#### 时间嘀嗒及系统级定时器实现(100%注释): 
 *   [tick_source.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/util/tick_source.h) 
 *   [system_tick_source.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/util/system_tick_source.cpp) 
 *   [system_tick_source.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/util/system_tick_source.h) 
 *   [timer.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/util/timer.cpp) 
 *   [timer.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/util/timer.h) 

#### mongod/mongos服务入口处理(100%注释): 
 *   [service_entry_point_mongod.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/service_entry_point_mongod.h) 
 *   [service_entry_point_mongod.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/service_entry_point_mongod.cpp) 
 *   [service_entry_point_mongos.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/service_entry_point_mongos.h) 
 *   [service_entry_point_mongos.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/service_entry_point_mongos.cpp)

#### command命令处理模块(注释进行中): 
 *   [commands.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/commands.h) 
 *   [commands.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/commands.cpp) 
 *   [write_commands.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/commands/write_commands/write_commands.cpp) 
 *   [cluster_write_cmd.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/commands/cluster_write_cmd.cpp)
 *   [strategy.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/commands/strategy.cpp)
 
#### shard分片源码实现(注释进行中):   
###### 分布式锁实现源码注释分析(100%注释): 
 *   [dist_lock_catalog_impl.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/dist_lock_catalog_impl.cpp) 
 *   [dist_lock_catalog_impl.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/dist_lock_catalog_impl.h) 
 *   [dist_lock_manager.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/dist_lock_manager.cpp) 
 *   [dist_lock_catalog.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/dist_lock_catalog.h) 
 *   [dist_lock_catalog_impl.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/dist_lock_catalog_impl.cpp) 
 *   [dist_lock_catalog_impl.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/dist_lock_catalog_impl.h) 
 *   [dist_lock_catalog_impl.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/dist_lock_catalog_impl.cpp) 
 *   [dist_lock_manager.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/dist_lock_manager.cpp) 
 *   [type_lockpings.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_lockpings.cpp) 
 *   [type_lockpings.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_lockpings.h) 
 *   [type_locks.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_locks.cpp) 
 *   [type_locks.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_locks.h) 
 *   [configsvr_enable_sharding_command.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/s/config/configsvr_enable_sharding_command.cpp) 

###### 代理定期更新config.mongos实现源码注释分析(100%注释): 
 *   [sharding_uptime_reporter.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/sharding_uptime_reporter.cpp)
 *   [sharding_uptime_reporter.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/sharding_uptime_reporter.h)
 *   [type_mongos.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_mongos.cpp)
 *   [type_mongos.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_mongos.h)

###### cfg复制集库表结构管理(config.databases、config.collections)(100%注释): 
 *   [type_collection.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_collection.cpp)
 *   [type_collection.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_collection.h)
 *   [type_database.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_database.cpp)
 *   [type_database.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/catalog/type_database.h)

###### 分片片建shard key(100%注释): 
 *   [shard_key_pattern.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/shard_key_pattern.cpp)
 *   [shard_key_pattern.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/s/shard_key_pattern.h)
 *   [keypattern.cpp](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/keypattern.cpp)
 *   [keypattern.h](https://github.com/y123456yz/reading-and-annotate-mongodb-3.6.1/blob/master/mongo/src/mongo/db/keypattern.h)
 
mongodb存储引擎wiredtiger源码分析  
===================================  
https://github.com/y123456yz/reading-and-annotate-wiredtiger-3.0.0   
  
  
rocksdb存储引擎源码分析  
===================================  
https://github.com/y123456yz/reading-and-annotate-rocksdb-6.1.2   
  



