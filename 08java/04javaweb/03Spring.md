# 1. 模块
1. 支持IoC和AOP的容器
2. 支持JDBC和ORM的数据访问模块
3. 支持声明式事务的模块
4. 支持基于Servlet的MVC开发
5. 支持基于Reactive的web开发
6. 集成JMS JavaMail JMX 缓存等模块

# 2. IoC容器
Spring通过IoC容器，对组件进行生命周期管理和配置组装服务  
## 2.1 Ioc要解决的问题
1. 谁负责创建组件？
2. 谁负责根据依赖关系组装组件？
3. 销毁时，如何按照依赖关系正确销毁？
## 2.2 Ioc机制
1. 所有组件，不在由应用程序自己创建和配置，而是由Ioc容器负责，将组件的使用和组件的配置创建分离
2. 在Spring的IoC容器中，把所有的组件统一称为JavaBean，即配置一个组件，就是配置一个Bean
```xml
<beans>
    <bean id="dataSource" class="HikariDataSource" />
    <bean id="bookService" class="BookService">
        <property name="dataSource" ref="dataSource" />
    </bean>
    <bean id="userService" class="UserService">
        <property name="dataSource" ref="dataSource" />
    </bean>
</beans>
```
3. Spring的IoC容器同时支持属性注入和构造方法注入，并允许混合使用
4. @Component 相当于定义了一个Bean
5. 使用@Autowired就相当于把指定类型的Bean注入到指定的字段中










