package java.interceptFilter;
/**
 * 拦截过滤器模式（Intercepting Filter Pattern）用于对应用程序的请求或响应做一些预处理/后处理。
 * 定义过滤器，并在把请求传给实际目标应用程序之前应用在请求上。
 * 过滤器可以做认证/授权/记录日志，或者跟踪请求，然后把请求传给相应的处理程序。
 * 以下是这种设计模式的实体
 * 过滤器（Filter） - 过滤器在请求处理程序执行请求之前或之后，执行某些任务。
 * 过滤器链（Filter Chain） - 过滤器链带有多个过滤器，并在 Target 上按照定义的顺序执行这些过滤器。
 * Target - Target 对象是请求处理程序。
 * 过滤管理器（Filter Manager） - 过滤管理器管理过滤器和过滤器链。
 * 客户端（Client） - Client 是向 Target 对象发送请求的对象。
 * 
 * 
 * 步骤一：创建过滤器接口 Filter。
 * 步骤二：创建实体过滤器。
 * 步骤三：创建 Target。
 * 步骤四：创建过滤器链。
 * 步骤五：创建过滤管理器
 * 步骤六：创建客户端 Client。
 * 步骤七：使用 Client 来演示拦截过滤器设计模式。
 */
public class InterceptingFilterDemo{
    public static void main(String[] args) {
        /**
         * 客户端要设置filtermanager 然后发送请求
         * filterManager是管理filterchain的 管理增减filter
         * filterchain 就是按照顺序直接filter 最后执行target的服务
         * target是filter后面最后一层的执行服务
         * 
         */
        FilterManager filterManager = new FilterManager(new Target());
        filterManager.setFilter(new AuthenticationFilter());
        filterManager.setFilter(new DebugFilter());

        Client client = new Client();
        client.setFilterManager(filterManager);
        client.sendRequest("hello world");
    }
}