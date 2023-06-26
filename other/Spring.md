# 自动装配

```java
//自动装配
//在xml中 一个bean标签的属性
<bean id="" class="" autowire="">
</bean>
byName:会自动在容器上下文中查找，和自己对象set方法后面值对应的bean的id
如 setDog(Dog dog) 就会在容器中找dog 找的是参数名 就是Dog dog中的dog
byType:和对象属性类型相同的bean，这种类型只出现一次
```

```java
@Autowire
@Qualifier(value="")这个指定bean的id 当类型一样的bean多时可以用这个


@Nullable  这个表示值可以为空
    
@Resource  
@resource(name="")指明id
```

Autowire和Resource

都是自动专配

Autowire默认byType

Resource默认byName，找不到就byType 否则报错

# 注解开发

**使用注解要导入约束，相应包**

AOP

**指定扫描的包**



@Component

```
等价于<bean id="user" class="pojo.User"/>
@Component
public class User{
	String str=""
}
id 默认是小写
```

- dao @Repository
- service @Service
- controller @Controller
- 功能和component是一样的



@value

```
@Value()
简单注入
复杂还是用xml
```

@Scope 作用域

@Bean

注意：

1. 如果开启包扫描，加载配置类以后就可以通过反射拿到配置类中的对象了，

2. @Bean只写在方法上，返回的是一个对象，但一般不获取已经在容器中的对象
2. @Bean 可以用于通过方法获取数据库连接池Connection这种对象

```
@Bean//方法的名字就是id  getBean的时候输入这个方法的名字
public User user()
{
	return new User();
}
```



最佳配合

- xml管理bean
- 注解完成属性注入



# 用java配置spring

@Configuration

它也是个component 代表是配置类，就是bean xml

就可以@ComponetScan("") @Import()

其实就是用java代码代码applicationConfiguration.xml

如果用了这个 要用AnnotationConfig去获取上下文





# 代理模式

代理模式有静态和动态

代理扮演的就是中介的角色

## 静态

- 抽象角色：接口或者抽象类
- 真实角色：被代理的角色                               --房东
- 代理角色：代理真实角色，代理真实角色后，我们一般会做一些附属操作    --房屋中介
- 客户：访问代理对象的人                    --租房的人

```java
public class User
{
	public void A(){}
	public void B(){}
}
```

```java
public class Proxy
{
	private User user;
	void setUser(User user)
	{
		this.user = user;
	}
	void A()
	{
		user.A();
	}
	...
	下面就是其他方法
	void B()
	{
		log("B");
		user.B();
	}
	void log(String str)
	{
	
	}
	
}
```



**AOP就是代理模式的体现**  

纵向开发

横向的切入 增加一些功能



代理做了很多事情，房东把租房给中介，然后中介做了其他事情。

缺点：一个真实角色对应一个代理



## 动态

代理类是动态生成

一个代理类既可以生成很多代理类

### 基于接口

Proxy

InvocationHandler

```java
public ProxyInvocationHandler implements InvocationHandler
{
    //被代理的接口
    private Rent rent;//Rent是一个接口
    ...很多接口
    public void setRent(Rent rent)
    {
        this.rent = rent;
    }
    public void Object getProxy()
    {
        return Proxy.newProxyInstance(this.getClassLoader(),rent.getClass().getInterface(),this);
    }
    //处理代理实例，并返回结果
	public Object invoke(Object proxy,Method method, Object[] args) throws Throwable
	{
        //动态代理的本质就是使用反射机制实现
        //res前后可以加代码，就是附属操作
        ...
		Object res = method.invoke(rent,args);
        return res;
        ...
	}
}
```



```java
public class Client
{
    //真实角色
	Host host = new Host();
    
    ProxyInvocationHandler pih = new ProxyInvocationHandler();
    
    //通过调用程序处理角色来处理我们要调用的接口对象
    pih.setRent(host);//host是rent的实现
    
    //这里就自动生成代理类 也就是静态代理里面的Proxy类 上面的
    Rent proxy = (Rent) pih.getProxy();
    
    proxy.rent();
    
}
```



### 基于类



# 反射

也就是反过来拿东西



# AOP

## spring API

```xml
注册bean
<bean id="A" class =""></bean>
<bean id="B" class =""></bean>
<bean id="C" class =""></bean>

<aop:config>
	切入点 可以多个
    <aop:pointcut id="pointcut1" expression="execution(.....[这里是表达式 有对应的A])"/>
    <aop:pointcut id="pointcut2" expression="execution(.....[这里是表达式])"/>
    
    执行
    <aop:advisor advice-ref="B" pointcut-ref="pointcut1"/>
    <aop:advisor advice-ref="C" pointcut-ref="pointcut1"/>
</aop:config>
```

```java

getBean("A"); A就是被加强的类
```



## 自定义

```xml
注册bean
<bean id="A" class =""></bean>
<bean id="B" class =""></bean> B是自定义的类，也就是没有实现spring API的接口

<aop:config>
    自定义的B 也就是切入面
    <aop:aspect ref="B">
        切入点
        <aop:pointcut id="pointcut1" expression="execution(.....[这里是表达式 有对应的A])"/>
        通知，也就是方法
        <aop:before method="B类中的方法" pointcut-ref="pointcut1"/>
        <aop:after method="B类中的方法" pointcut-ref="pointcut1"/>
    </aop:aspect>

</aop:config>
```



## 注解

@Aspect 表示这个类是切面，就是上面的B

```java
@Aspect
public class A
{
    @Before("execution()")
    public void before();
}
```



# 声明式事务

事务要么都成功，要么都失败 ACID

数据库讲过

**配置声明式事务**

**结合AOP**

transactionMannger



# MVC

## Controller

取得表单数据

调用业务逻辑

转向指定的页面

## Model

业务逻辑

保存数据的状态

## View

显示页面



# SpringMVC

没有什么是不能加一层解决不了的

## 注解开发

注解要扫描包和配置一些东西

配置好后

```java
@Controller
//如果在类上@RequestMapping("A") 下面的hello就会是/A/hello
public class HelloController
{
    @RequestMapping("/hello")//访问地址 只要是String函数返回就行
    public String hello(Model model)
    {
        //封装数据
        model.addAttributr("msg","Hello");
        return "hello";//会被试图解析器解析，返回hello.jsp
	}
}
```

## RESTful风格

传统           localhost:8080/key=value

RESTful     localhost:8080/value



```java
@Controller
//如果在类上@RequestMapping("A") 下面的hello就会是/A/hello
public class HelloController
{
	//origin localhost:8080/add?a=1&b=2
    //RESTful localhost:8080/add/a/b
    @RequestMapping("/add/{a}/{b}")//访问地址 只要是String函数返回就行
    public String hello(@PathVariable int a,@PathVariable int b,Model model)//@PathVariable 就把a映射到RequestMapping中的{a}
    {
        //封装数据
        model.addAttributr("msg","Hello");
        return "hello";//会被试图解析器解析，返回hello.jsp
	}
    
    @RequestMapping(value="/add/{a}/{b}",method=RequestMethod.GET)指定get方法
    @GetMappinng("/add/{a}/{b}")
    @PostMapping("/add/{a}/{b}")
}
```

## 重定向和转发

重定向就直接return "forward:url"; 或者不用写forward

转发 return "redirect:/index.jsp";



重定向会改变地址栏  

转发不会



## 接收参数和数据回显

有lombok就可以不用写set和get和有参，无参构造



```java
public String UserController
{
    @GetMapping("t1")//这里传参的名字要和这里的名字一样
    public String test(String name,Model model)
    {
        //接收前端参数
        
        //返回结果
        
        //跳转
        return "test";
    }
    @GetMapping("t1")//前端的参数名字是username
    public String test(@RequestParam("username") String name,Model model)
    {
        //接收前端参数
        
        //返回结果
        model.addAtrribute("","");
        //跳转
        return "test";
    }
    @GetMapping("t1")//注意，表单域和对象属性名一致
    public String test(User user)
    {
        //接收前端参数
        
        //返回结果

        //跳转
        return "test";
    }
    @GetMapping("t1")
    public String test(ModelMap mode)
    {
        //接收前端参数
        
        //返回结果

        //跳转
        return "test";
    }
    
    
}
```



## 乱码

过滤器

```java
在web.xml中 配置Spring过滤器
```



## Jackson

导入包

```java
@RequestMapping(value="/A",produces="application/json;charset=utf-8")//解决中文问题
@ResponseBody//他就不会走视图解析器，直接返回字符串 返回数据
public String json()
{
    User user = new User("","","");
    ObjectMapper mapper = new ObjectMapper();
    String str = mapper.writeValueAsString(user);
    return str;
}
```



```
乱码问题配置
配置springmvc-servlet.xml
就可以不用produces
```



```
@RestController直接返回字符串 后面不用@ResponseBody
@Controller 会走视图解析
```



## fastJson





serive 调用dao



## Ajax

改变<iframe> 改变src的地址  

静态资源过滤

```(
$ 表示jQuery
$.ajax(
    {
    url:
    data:
    success:
}
)
$.post({
    url:"${pageContext.request.contexPath}/a1",
    data:{"name"=$("#username").val()},//#username 是选择id为username的元素
    seccess:function(data)//这是个callback函数
        {
            
        }   
})

$.post("url","参数可以被省略",function(data){
	data是返回的数据
})
```





## 拦截器

类似过滤器 

类似配置

只在Controller起作用

自定义拦截器，继承HandlerInterceptor

他是AOP思想的具体体现

/*当前

/**当前下所有文件

就是对Controller进行AOP操作





## 文件上传和下载

**前端要设置表单中enctype为multipart/form-data**

```
配置文件上传的xml


```





# Vue

**官网文档还不错**

根据数据变化，立即刷新

双向绑定 MVVM

DOM监听

## 基本语法

el     element

{{}}

v-bind

```html
<div id="app">
    <a v-if="ok">YES</a>  下面的ok为true，这里YES就会显示
    <a v-else>NO</a>
</div>

<div id="app">
    <a v-if="type==='A'">YES</a>  下面的ok为true，这里YES就会显示
    <a v-else-if="type==='B'">NO</a>
    <a v-else></a>
</div>

<script src=""></script>导入vue的cdn
<script>
	var vm = new Vue({
        el: "#app",//选择器
        data: {
            ok : true
            type : 'A'
        }
    })
</script>
```



```html
<div id="app">
	<li v-for="item in items">
        {{item.message}}
    </li>
</div>


<script src=""></script>导入vue的cdn
<script>
	var vm = new Vue({
        el: "#app",//选择器
        data: {
            items: [
                {message: "A"},
                {message: "B"}
            ]
        }
    })
</script>
```



## 事件

```html
<div id="app">
    <button v-on:click="sayHi">
        click me
    </button>
</div>

<script>
    var vm = new Vue({
    el : "#app",
    data : {msg: "A"},
    methods : {
        sayHi: function(event)
        {
            alert(this.msg);
        }
    }
});
</script>
```



## 双向绑定

用v-model就绑定了

```html
<div id="app">
<   v-model="msg">{{msg}}
    v-model绑定其中一个属性
</div>

<script src=""></script>导入vue的cdn
<script>
	var vm = new Vue({
        el: "#app",//选择器
        data: {
			msg: ""
        }
    })
</script>
```



## 组件

```html
<div id="app">
    把item绑定到qin
    <C1 v-for="item in items" v-bind:qin="item"></C1>
</div>


<script>
    //C1 是对应的标签
	Vue.component("C1",{
       props:['qin'],//接收参数
       template:  '<li>{{qin}}</li>'
    });
    var vm = new Vue({
        el: "#app",
        data: {
            items: ["A","B","C"]
        }
    });

</script>
```



## Axios

主要作用是实现ajax

导入axios

```html
<div id="app">
    <div>
        {{info.name}}
    </div>
    <a v-bind:href="info.url">click</a>
</div>

<script>
    var vm = new Vue({
        el: "#app",
        data(){
          return {
              //请求返回参数合适，必须和json字符串一样
              info:{
                  name: null,
                  ...
              }
          }  
        },
		mounted(){//链式编程   钩子函数
            axios.get('url').then(response=>(console.log(response.data)));
        }
    });

</script>
```

## 计算属性

```html
<div id="app">
	<p>
        {{A()}}
    </p>
    <p>
       	{{B}}
    </p>
</div>

<script>
    var vm = new Vue({
        el: "#app",
    	data: {msg: "hello"},
        methods: {
            A: function()
            {
                return Date.now();
            }
        },
        computed: {//计算属性 重名之后只会掉methods中
            B: function()//这个是属性，保存在内存，类似缓存
            {
                
            }
        }
    
    })

</script>
```



## slot

插槽

```html
<div id="app">
<todo>
	<todo-t slot="todo-t" :title="title">{{title}}</todo-t>    
</todo>
</div>

<script>
    
    Vue.component("todo",{
       template: '<div>' +'<slot name="todo-t"></slot>'+'</div>'   
    });
    
    Vue.component("todo-t",{
        props: ["title"]
       template: '<div>{{title}}</div>'   
    });
    var vm = new Vue({
        el: "#app" 
        data: {
        title="D",
        items:["A","B","C"]
    }
    })

</script>
```



## 自定义事件

v-blind: 简写就一个:

this.$emit();



# vue-cli

```
npm install vue-cli -g

vue list 查看

vue init webpack myvue

cd myvue

npm install 根据package.json下载 类似maven

npm run dev 启动项目

```



### webpack

js静态模块打包器



export 导出

require 导入



```
npm install webpack -g
npm install webpack-cli -g
```

#### 打包

modules文件下 下面两个文件

```js
hello.js
//暴露一个方法
export.func = function()
{

}
```

```js
main.js
//接收
var hello = require('./hello');
hello.func();
```



写webpack.config.js

```js
module.exports={
    entry: './modoles/main.js',
    output: {
        filename: "./js/bundle.js"
    }
}
```

然后执行webpack命令打包



### Router

```
npm install vue-router --save-dev
```

```js
config/index.js  配置文件
代码
导入Vue，VueRouter 和自己写的component
//安装路由
Vue.use()

//配置导出路由
export default new VueRouter({
	routes: [
	{
        //路由路径 也就是地址栏会显示的 这个就是@RequestMapping
		path: '/A'
        name: 'A',
        componen: 这里就是导入的component
	}，
    {
        
    }
	]
});
```



在main.js中

```js
导入上面的路由
加入路由
import elementui的css
Vue.use(router);
Vue.use(ElementUI)
在new Vue({
    el: "#app",
    router,   
    render: h=>h(App)//elementUI 官网的
})
```

如何跳转

```html
<router-lick to="/A">A</router>这里就是路由注册的path
<router-view></router-view>
```





# element-ui + Vue

```
cd hello-vue

npm install vue-router --save-dev

npm i element-ui -S

npm install 
//安装SASS和加载器
npm install sass-loader node-sass -save-dev

npm run dev
```

还有lay ui



```
导入上面的路由
加入路由
import elementui的css
Vue.use(router);
Vue.use(ElementUI)
在new Vue({
    el: "#app",
    router,   
    render: h=>h(App)//elementUI 官网的
    				 //这里App是一个App.vue文件，就是给这个文件渲染，在这个文件中加入<router-view>
    
})
```

如何出错，又可以是sass-loader版本太高

改版本再npm install



**docify**



# 嵌套路由

```js
//配置导出路由
export default new VueRouter({
	routes: [
	{
        //路由路径 也就是地址栏会显示的 这个就是@RequestMapping
		path: '/A'
        name: 'A',
        componen: 这里就是导入的component,
        children :[
        {path: '/B',component: },
        ...
        ]
	}，
	]
});
```

然后加上\<router-link to=""\>



# Vue传参



```
<router-link v-bind:to="{name="/B",params:{id:1}}">
```



```
	{
        //路由路径 也就是地址栏会显示的 这个就是@RequestMapping
		path: '/A'
        name: 'A',
        componen: 这里就是导入的component,
        children :[
        {path: '/B/:id',component: },
        ...
        ]
	}，
```



```
{{$route.params.id}} 就可以在前端展现
这个要包含在标签里面如<div>
```

看官方文档 实现登录进去后显示用户名



重定向

```
{
	path:
	redirect:
}
```



```
# hash模式
  history模式
在路由里面设置model

```



# Vue路由钩子

```js
//类似AOP
export default{
    props: ['id'],
    name: "", 对应的component的name属性
    beforeRouteEnter:(to,from,next)=>
    {
		next(vm=>{
            vm.getData();
        });
    }
    beforeRouteLeave:(to,from,next)=>
    {
		next();
    }
}
```

可以配合axios配置



# 语法糖

就是加语法





# 微服务

把service独立出来



# Springboot

在Application.java的同级目录下建立包

pojo

dao

service



```
在properties文件下可以配置

server.port=
```



自定义banner.txt

## 原理



pom.xml

- spring-boot-dependencies: 核心依赖在父工程中
- 不用写版本号，因为有版本库

启动器

- 各种start



主程序

- 那个注解包含了springboot配置 也是个组件
- 自动配置



## 配置文件

注释还是#

application.properties

- key=value

```
name=A
student.name=B
student.age=12
```

application.yml

- key:空格 value

```yaml
#普通键值对
name: A

#对象
student: 
  name: B
  age: 12
  
#行内写法
student: {name: A,age: 12}

#数组
pets:
  - cat
  - dog
  - pig
pets: [cat,dog,pig]
```

yaml可以注入

对应java类写属性和值

如何注入呢？

 **@ConfigurationProperties(prefix="person")**

```yaml
person:
  name: A
  ...
  age: ${random.int}
  id: ${random.uuid}
  att: ${}_value  如果{}不存在就用后面的value
```



如果用properties

**@PropertySource(value="路径")**

取值的话用@Value("${name}") 使用SPEL表达式



**JSR-303**

@Validated数据校验

- @Email("邮箱格式错误")



**切换**

多环境配置

```
#切换到application-test.properties
spring.profiles.active=test
```



```yaml
#使用yml
server:
  port: 8081
Spring: 
  profiles: 
    active: dev

---
server:
  port: 8082
Spring: 
  profiles: 
    active: dev

---
server:
  port: 8083
Spring: 
  profiles: 
    active: test
```



## web开发

处理静态资源

- webjar
- public,static /**,resouces
- 优先级resources>static>public
- 源码上有



thymeleaf

加入依赖 

把html放在templates里面

官网有使用方法

## springdata

在resources下

加入application.yml

```yml
spring:
  datasource:
  username:
  password:
  url:
  driver-class-name:
```



```java
@Auouwired
DataSource dataSource;
void test()
{
	Connection con = dataSource.getConnection();
    然后就可以进行
}
```



有个JdbcTemplate



## druid数据源

配置里面加入type: 阿里的druid

里面可以防止sql注入



```java
@Configuration
public class DruidConfig
{
    @ConfigurationProperties(prefix="spring.datasource")
    @Bean
    public DataSource druidDataSource()
    {
        return new DruidConfig();
    }
    
    //后台监控 
    @Bean
    public ServletRegistrationBean s()//代替web.xml
    {
        //配置初始参数
    }
}

```



## mybatis

```
@Mapper
@Repository
public interface UserMapper
{
}
```



## SpringSecurity

还可以shiro

身份验证和权限认证



WebSecurityConfigureAdapter

Authentication

配置

```java

#EnableWebSecurity
public class SecurityConfig entends WebSecurityConfigureAdapter
{
    @Override
    public void configure(HttpSecurity http)throw Exception
    {
        //链式编程
        //请求授权的规则
        http.authorizeRequest()
            .antMatchers("/").permitAll()
            .antMatchers("/levell1/**").hasRole("vip1")
            .antMatchers("/levell2/**").hasRole("vip2");
        
        //没有权限 默认登录页面
        http.formLogin();
        //注销
        http.logout();   看源码就知道怎么玩
            
        //防止网站工具
        http.scrf().disable();
    }
    
    //密码编码
    //加密
    @Override
    protected void configure(AuthenticationManagerBuilder auth)throw Exception
    {
        //这些数据应该在数据库中
        auth.inMemoryAuthentication().passwordEncoder(new 根据提示)
            .withUser("username").password("").roles("vip2")
            .and()
            .withUser....password(new 某个Encoder().encode(""))
            加其他user
    }
}
```



# Swagger

postman 工具

需要springbox

导入依赖

```
swagger2

swagger-ui
```



```java
@Configuration
@EnableSwagger2//开启swagger
public SwaggerConfig//
{
	@Bean
	public Docket decket()
    {
        return new Docket(DocumentationType.SWAGGER_2)
            .apiInfo(apiInfo())
    }
    //配置基本信息
    private ApiInfo apiInfo()
    {
        Contact contact = new Contact();//有很多参数，懒得写了
        return new ApiInfo(
        //填参数就行了
        )
    }
    
    
    
}
```

运行: localhost:8080/swagger-ui.html



Swagger配置扫描接口

```
@Configuration
@EnableSwagger2//开启swagger
public SwaggerConfig//
{
	@Bean
	public Docket decket()
    {
    	//设置要显示的swagger环境
    	Profiles p = new Profile.of("dev","test");
    	//通过environment.acceptsProfiles判断是否处在自己设定的环境中
    	boolean flag = environment.acceptsProfiles(p);
        return new Docket(DocumentationType.SWAGGER_2)
            .apiInfo(apiInfo())
            .enable(flag)//布尔值 是否启动swagger
            .select()
            .apis(RequestHandlerSelectors.basePackage(""))
            .paths(PathSelector(""))//过滤
            .build();
    }
}
```



配置组名字

```
.groupName("A")
```

配置多个组，就是多个Docket

```
	@Bean
	public Docket decket1(){return new Docket()}
	@Bean
	public Docket decket2(){return new Docket()}
	@Bean
	public Docket decket3(){return new Docket()}
```



```
@ApiModel("") //加实体类注释
```



# 任务

## 异步任务

```java
@Service
public class AsyncTasks()
{
    @Asyn
    public test()
    {
        try
        {
            Thread.sleep(3000);
        }
        catch()
        {
            
        }
        sout("")
    }
}
```

然后在启动类上加上

```
@EnableAsync
```

## 邮件

加入依赖

配置文件

```
spring.mail.username=
...
```



## 定时任务

TaskSheduler

TaskExecutor



@EnableScheduling

@Scheduled

Cron表达式



```java
@Scheduled(cron="")
public void hello()
{
    ...
}
```



# 分布式

分布式系统是若干独立计算机的集合，这些计算机对于用户来说就像单个相关系统

通过网络通信

Nginx代理服务器

Dubbo



RPC: remote procedure call 只是一种技术的思想 核心为通讯和序列化

序列化：数据传输需要转换



zookeeper(注册中心)下载压缩包，如果有启动有问题时cfg文件

dubbo-admin 监控管理后台





导入dubbo和zookeeper(client)的依赖

有日志冲突

配置properties

```
server.port=
#服务应用名字
dubbo.application.name=
#注册中心地址，也就是zookeeper
dubbo.registry.address=zookeeper://127.0.0.1:
#哪些服务被注册
dubbo.scan.base-package=
```

```
注解用@Component
@Service用dubbo的
```

后台开启dubbo的jar jar包自己打包



拿到服务

```
@Reference//引用 pom坐标，可以定义路径相同的接口名
```



步骤

zookeeper服务一定要开启

1.提供者提供服务

- 导入依赖
- 配置注册中心的地址，服务发现名，扫描的包
- 在向被注册的服务上增加注解@Service 用dubbo的

2.消费者使用

- 导入依赖
- 配置注册中心的地址，服务自己发现名，扫描的包
- 从远程注入服务



# Springcloud

```xml
<properties>
<a.version>1.1.1</a.version>
</properties>

<dependency>
<version>${a.verison}</version>
</dependency>
```



```java
@Accessors(chain=true)链式
public class Dept implements Serializable
{
    
}
```



提供者

要拿到实体类 配置自己写的



热部署

Devtools



Eureka

Eureka集群



Ribbon 负载均衡

LoadBalance 将用户的请求平摊分配到多个服务上



















