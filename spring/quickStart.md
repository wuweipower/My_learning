https://start.spring.io/

添加spring web依赖

点击create 下载

使用IDEA打开

编写一下代码

```
@SpringBootApplication
@RestController
public class DemoApplication {
    public static void main(String[] args) {
      SpringApplication.run(DemoApplication.class, args);
    }
    @GetMapping("/hello")
    public String hello(@RequestParam(value = "name", defaultValue = "World") String name) {
      return String.format("Hello %s!", name);
    }
}
```

执行

```
./gradlew bootRun#mac/linux
```

```
.\gradlew.bat bootRun#win
```

基本的hello world就有了

