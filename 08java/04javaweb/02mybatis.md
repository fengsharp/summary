# 1. db
```sql
create table user (
    id int primary key,
    name varchar(30),
    pwd varchar(30)
) engine=innodb default charset=utf8;


insert into user(id, name, pwd) values
(1, 'aa', 'aaaaaaaaaaaaaaaaa'),
(2, 'bb', 'bbbbbbbbbbbbbbbbb'),
(3, 'cc', 'ccccccccccccccccc'),
(4, 'dd', 'ddddddddddddddddd');
```

# 2. 
mybatis mysql junit
```xml
<dependency>
  <groupId>org.mybatis</groupId>
  <artifactId>mybatis</artifactId>
  <version>x.x.x</version>
</dependency>

```

# 3. 
1. user domain
2. UserDao interface
3. UserMapper.xml 放到resources/mapper

```xml
<!--在build中配置resources，防止我们资源导出失败的问题-->
<build>
 <resources>
    <resource>
        <directory>src/main/resources</directory>
        <includes>
        <include>**/*.properties</include>
        <include>**/*.xml</include>
        </includes>
        <filtering>true</filtering>
    </resource>
    <resource>
        <directory>src/main/java</directory>
        <includes>
        <include>**/*.properties</include>
        <include>**/*.xml</include>
        </includes>
        <filtering>true</filtering>
    </resource>
 </resources>
</build>
```

# 4. 构建测试
1. pom.xml
```xml
<dependencies>
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>5.1.47</version>
    </dependency>
    <dependency>
        <groupId>org.mybatis</groupId>
        <artifactId>mybatis</artifactId>
        <version>3.5.6</version>
    </dependency>
    <dependency>
        <groupId>junit</groupId>
        <artifactId>junit</artifactId>
        <version>4.13.2</version>
        <scope>test</scope>
    </dependency>
    <dependency>
        <groupId>log4j</groupId>
        <artifactId>log4j</artifactId>
        <version>1.2.12</version>
    </dependency>
</dependencies>

<build>
    <plugins>
        <plugin>
            <groupId>org.apache.maven.plugins</groupId>
            <artifactId>maven-compiler-plugin</artifactId>
            <version>3.8.1</version>
            <configuration>
                <source>13</source>
                <target>13</target>
            </configuration>
        </plugin>
    </plugins>
</build>
```

2. resources add log4j.properties
```properties
log4j.rootLogger=DEBUG,A1
log4j.logger.org.apache=DEBUG
log4j.appender.A1=org.apache.log4j.ConsoleAppender
log4j.appender.A1.layout=org.apache.log4j.PatternLayout
log4j.appender.A1.layout.ConversionPattern=%-d{yyyy-MM-dd HH:mm:ss,SSS} [%t] [%c]-[%p] %m%n
```

3. create table
```sql
DROP TABLE IF EXISTS tb_user;
CREATE TABLE tb_user (
    id int NOT NULL,
    user_name varchar(32) DEFAULT NULL,
    password varchar(32) DEFAULT NULL,
    name varchar(32) DEFAULT NULL,
    age int(10) DEFAULT NULL,
    sex int(2) DEFAULT NULL,
    birthday date DEFAULT NULL,
    created datetime DEFAULT NULL,
    updated datetime DEFAULT NULL,
    PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

INSERT INTO tb_user (id, user_name, password, name, age, sex, birthday, created, updated) VALUES ( 1, 'zpc', '123456', 'aa', 22, 1, '1990-09-02', sysdate(), sysdate());
INSERT INTO tb_user (id, user_name, password, name, age, sex, birthday, created, updated) VALUES ( 2, 'hj', '123456', 'bb', 22, 1, '1993-09-05', sysdate(), sysdate());
```

4. domain User
```java
private int id;
private String userName;
private String password;
private String name;
private Integer age;
private Integer sex;
private Date birthday;
private String created;
private String updated;
```

5. utils
```java
public class MybatisUtils {
    private static SqlSessionFactory sqlSessionFactory;
    static {
        try {
            String resource = "mybatis-config.xml";
            InputStream inputStream = Resources.getResourceAsStream(resource);
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static SqlSession getSqlSession() {
        return sqlSessionFactory.openSession();
    }
}
```

6. mapper(dao) interface
UserMapper
```java
public interface UserMapper {
    List<User> getUserList();
}
```
7. mapper.xml resources/mapper/UserMapper.xml
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.sharp.dao.UserDao">
    <select id="getUserList" resultType="com.sharp.domain.User">
        select * from tb_user;
    </select>
</mapper>
```

8. resources/mybatis-config.xml
```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <environments default="development">
        <environment id="development">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <property name="driver" value="com.mysql.jdbc.Driver"/>
                <property name="url" value="jdbc:mysql://192.168.154.128:3306/study?useSSL=false"/>
                <property name="username" value="root"/>
                <property name="password" value="Love_321"/>
            </dataSource>
        </environment>
    </environments>
    <mappers>
        <mapper resource="mapper/UserMapper.xml"/>
    </mappers>
</configuration>
```

9. test code
```java
try (SqlSession sqlSession = MybatisUtils.getSqlSession()) {
    UserMapper mapper = sqlSession.getMapper(UserMapper.class);
    List<User> userList = mapper.getUserList();
    for (User user : userList) {
        System.out.println(user);
    }
} catch (Exception ex) {
    ex.printStackTrace();
}
```

10. 接口参数配置
    1. 一个参数
```java
User queryUserById(@Param("id")int id); // @Param("id")可以省略
```

```xml
    <select id="queryUserById" resultType="com.sharp.domain.User">
        select * from tb_user where id = #{id}
    </select>
```

    2. insert 
```java
void insertUser(User user);
```

```xml
    <insert id="insertUser" parameterType="com.sharp.domain.User">
        insert into tb_user(id, user_name, password, name, age, sex, birthday, created, updated) values
        (#{id}, #{userName}, #{password}, #{name},#{age},#{sex},#{birthday},#{created},#{updated})
    </insert>
```

    3. update
```java
void updateUser(User user);
```

```xml
    <update id="updateUser" parameterType="com.sharp.domain.User">
        update tb_user set birthday = #{birthday}, created = #{created}, updated=#{updated} where id = #{id}
    </update>
```

    4. delete
```java
void deleteUser(User user);
```

```xml
    <delete id="deleteUser" parameterType="com.sharp.domain.User">
        delete from tb_user where id = #{id}
    </delete>
```


# 5. #和$的区别
<select id="queryUserListByName1" resultType="com.zpc.mybatis.pojo.User">
    select * from tb_user WHERE user_name=#{username1}
</select>

<select id="queryUserListByName2" resultType="com.zpc.mybatis.pojo.User">
    select * from tb_user WHERE user_name='${username2}'//手动加了引号
</select>


# 6. 缓存
1. 默认开启了session，原理：同一个session中， 执行sql前，先在cache中判断是否匹配成功，失败才会执行
2. sqlSession.clearCache();可以强制清除缓存
3. 执行update、insert、delete的时候，会清空缓存
4. mybatis 的二级缓存的作用域是一个mapper的namespace ，同一个namespace中查询sql可以从缓存中命中。需要在mapper.xml中开启
5. 开启二级缓存，domain实体类必须序列化 implements Serializable












