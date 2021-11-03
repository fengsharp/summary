# 1. 常用注解
资料来源：https://zhuanlan.zhihu.com/p/395766827  
## 1.1 MVC
1. RequestMapping 搭配 Controller或者RestController
    - GetMapping  @RequestMapping(method=RequestMethod.GET)的快捷方式
    - PostMapping @RequestMapping(method=HttpMethod.POST)的快捷方式
    - PutMapping  @RequestMapping(method=HttpMethod.PUT)
    - DeleteMapping @RequestMapping(method=HttpMethod.DELETE)
    - PatchMapping @RequestMapping(method=HttpMethod.PATCH)
2. RequestBody 针对请求参数
3. Valid针对请求参数
4. ResponseBody 自动将控制器中方法的返回值写入到HTTP响应中 搭配 @Controller
5. RestController @Controller + @ResponseBody
6. ResponseStatus注解可以标注请求处理方法。使用此注解，可以指定响应所需要的HTTP STATUS
7. PathVariable注解是将方法中的参数绑定到请求URI中的模板变量上 允许使用value或name属性来给参数取一个别名  
模板变量名需要使用{ }进行包裹，如果方法的参数名与URI模板变量名一致，则在@PathVariable中就可以省略别名的定义  
```java
@GetMapping("/users/{id}/roles/{roleId}")
public Role getUserRole(@PathVariable(name="id") long id, @PathVariable(value="roleId") long roleId) {
}
```
8. RequestParam注解用于将方法的参数与Web请求的传递的参数进行绑定 defaultValue设置一个默认值
9. @Controller是@Component注解的一个延伸
10. CrossOrigin注解将为请求处理类或请求处理方法提供跨域调用支持

## 1.2 Spring Bean
1. ComponentScan注解用于配置Spring需要扫描的被组件注解注释的类所在的包
2. Component注解用于标注一个普通的组件类，它没有明确的业务范围，只是通知Spring被此注解的类需要被纳入到Spring Bean容器中并进行管理
3. Service注解是@Component的一个延伸（特例），它用于标注业务逻辑类
4. Repository注解是@Component注解的延伸，被此注解标注的类会被Spring自动管理起来，@Repository注解用于标注DAO层的数据持久化类

## 1.3 容器配置
1. @Autowired注解用于标记Spring将要解析和注入的依赖项
2. @Autowired在进行依赖注入的时候就不知道该选择哪一个实现类进行注入, 此时，我们可以使用@Qualifier注解来微调



# 2. 简单工程
1. 模板创建
2. 选择组件
    - developer tools -> lombok
    - web -> spring web
    - template engine -> thymeleaf
    - sql -> mybatis framework | mysql

3. 修改配置 pom.xml
```xml
<properties>
    <java.version>13</java.version>
</properties>

<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>5.1.47</version>
    <scope>runtime</scope>
</dependency>
```
或者
```xml
<properties>
    <java.version>13</java.version>
    <mysql.version>5.1.47</mysql.version>
</properties>
```

4. resources/application.yml  
mkdir -p resources/mappers
```yml
server:
  port: 8899
  servlet:
    context-path: /
spring:
  datasource:
    url: jdbc:mysql://192.168.154.128:3306/study?useSSL=false
    driver-class-name: com.mysql.jdbc.Driver
    username: root
    password: Love_321
mybatis:
  mapper-locations: classpath:mappers/*Mapper.xml
  type-aliases-package: com.sharp.first.domain
```

5. application-main
```java
@MapperScan("com.sharp.first.dao")
```

6. 目录
```txt
controller
    UserController
service
    UserService
        UserServiceImpl
dao
    UserDao
domain
    User
```

7. code-domain
```java
@Data
@NoArgsConstructor
@AllArgsConstructor
@ToString
public class User {
    private int id;
    private String name;
    private String pwd;
}

```

8. code-dao
```java
public interface UserMapper {
    User findUser(int id);
}
```

9. code-mapper
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.sharp.first.dao.UserMapper">
    <select id="findUser" resultType="com.sharp.first.domain.User">
        select * from user where id = #{id};
    </select>
</mapper>
```

10. code-service
```java
public interface UserService {
    User findUser(int id);
}

@Service
public class UserServiceImpl implements UserService {
    @Resource
    private UserMapper userMapper;

    @Override
    public User findUser(int id) {
        return userMapper.findUser(id);
    }
}
```

11. code-controller
```java
@Controller
@RequestMapping("/user")
public class UserController {
    @Resource
    private UserService userService;

    @RequestMapping("/find")
    @ResponseBody
    public User findUser(int id) {
        return userService.findUser(id);
    }
}
```



