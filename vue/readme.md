# vue2

diff算法

数据->virtual dom->real dom



## 监视的原理

 首先是更新的问题，如果数据里面一个数组的东西用一个对象直接替代，但是vue检测不大

```
data:{
	persons:[
	{},
	{}
	]
}

this.persons[0]={} 这样vue检测不到变化
```



setter方法 在改变时 重新解析模板。

```js
data:{}
Object.defineProperty(data,'name'{
	get(){
    return data.name
},
    set(val){
       data.name.val 
}
})//这个代码巨大的问题就是，你修改和获取的时候会调用get和set但是，这又会引起修改和改变这个动作，因此又调用get和set 最后call stack溢出
```



```js
data:{}

const obs = new Observer(data);//检测data的变化

let vm = {}
vm._data = data = obs

//vm会递归所有属性，并且为之设置set和get
function Observer(obj){
    const keys = Obeject.keys(obj)
    keys.forEach((k)=>{
        Object.defineProperty(this,k,{
            get()
            {
                return obj[k]
            },
            set(val)
            {
                解析模板，生成虚拟dom
				obj[k] = val
            }
        })
    })
}
```



```js
//vm上追加属性
Vue.set(targetObj,key,val)
//不用给data和vm加属性
//必须是里面的
```



不能检测到数组 是因为没有对索引值的set和get 

```
this.persons[0]={} 这样vue检测不到变化 直接赋值不行
//vue检测push splice 等等7个
//不过vm管理的数组 里面的push包装过 除了使用array.prototype.push 还有解析
this.persons[0].splice(0,1,{})这个才能被检测到
```



ref

```html
<h1 id="title">
    
</h1>

变为
<h1 ref="title">
    
</h1>

如何获取
<script>
    console.log(this.$refs.title)//元素或子组件的信息
    等价于
    console.log(document.getElementById('title'))
</script>
```



pros

```html
在一个student的vue组件里

<template>
	<p>
        {{name}}
    </p>
    <p>
        {{age}}
    </p>
</template>
<script>
	export default{
        name:'student',
        data(){
            return {
                msg:'hello'
                myAge:this.age//这样的话就可以没有警告的修改age 操作myAge
            }
        },
        props:['name',age],//properties
        对于类型限制
        props:{
        name:String,
        age:Number
    },
        props:{
            name:{
                type:String,
                required:true,
            },
            age:{
                type:number,
                default:true,
            }
        }
        
    }

</script>

在app里面

<template>
	<div>     
        <student name="a",age="1"></student>
        <student name="a",:age="1"></student>这样就让"1" 变成js表达式 v-bind
    </div>
</template>

<script>
	export default{
		name:'App',
        components:{student},

    }
</script>
```



mixin

```js
mixin.js

export const mixin={
    methods:{
        show()
        {
            
        }
    }
}
```

```js
student.vue
import {mixin} from mixin

	export default{
        name:'student',
        data(){
            return {
                msg:'hello'
                myAge:this.age//这样的话就可以没有警告的修改age 操作myAge
            }
        },
        mixins:[mixin]//组合在一起 如果在本文件有该属性则不混合这个属性
    }
```

```
全局混入

Vue.mixin()
```



插件,增强效果

```
plugins.js

export default={
	install(vue)
	{
	console.log(vue)
}
}
```



```
main.js

import plugin from 'plugins'

Vue.use(plugin)
```



vue中style的时候会汇合app.vue 会有名字冲突

加个scoped就可以 了

lang指的是language

样式有css less

```
<style scoped>
</style>

```





如何让子组件和父组件传东西

父组件定义一个函数 将这个函数传过去 子组件在props里面定义这个就可以调用



如何添加



浏览器本地存储 浏览器关了还有

会话存储 浏览器关了就没了

```html
<script>
	function save()
    {
        localStorage.setItem('key','value')
    }
    function get()
    {
        localStorage.getItem('key')
    }
    localStorage.removeItem('key')
    localStorage.clear()
    JSON.parse()
    JSON.stringfy()

   	会话存储
    session.setItem   api是一样的
</script>
```





绑定自定义事件  子组件向父组件发送消息

```
student.vue
< @click='send'></>

send()
{
this.$emit('func',this.name)
}


app.vue
<student v-on:func='demo'>
demo(name)
{
	这样就获得name了
}

//还有一种方式
<student ref='student‘>
mouted()
{
this.$refs.student.$on('demo',this.demo)
}

```



```
解绑事件

this.&off(['func'])
```



destroye的时候 组件的自定义的事件会被销毁



## 全局事件总线：任意组件通信



```
基本思想
app.vue
Vue.prototype.x={a:1,b:2}
```





```
app.vue

new Vue{
	el:'#app',
	render: h=>h(App),
	beforeCreate()
	{
	Vue.prototype.$bus = this//安装事件总线 直接让这个vm作为通用
}
}
```



获取数据

```
school.vue

mouted(){
	this.$bus.$on('hello',(data)=>{
		console.log("i get data",data)//绑定事件
	})
}

beforeDestroye()
{
	this.$bus.$off('hello')
}


```

发送数据

```
student.vue

methods:{
	sendStuName()
	{
	this.$bus.emit('hello',666)
}
}
```





## pub/sub

```
npm i pubsub.js
```

```
import pubsub from 'pubsub-js'

school.vue

mounted()
{
	pubsub.subscribe('hello',function(msgName,data)
	{
		this.id = console.log(data)
	})
}

beforeDestroy()
{
	pubsub.unsubscribe(this.id)
}

```



```
student.vue

sendStuName()
{
	pubsub.publish('hello',data)
}
```



编辑

```html
<input v-show='isEdit'>
<span v-show='!isEdit'></span>

加入isEdit属性
handleEdit(todo)
{
	if(todo.hasOwnProperty('isEdit'))
	{
	this.isEdit=true
	}
	else
		this.$set(todo,'isEdit',true)
	this.$nextTick(function()
`	{
		this.$refs.inputTitle.focus()//下一次dom更新后调用 由于前面的isEdit改变了
	})//获得焦点

	另一种方法就是用setInterval()

}


//失去焦点的时候 修改
handleBlur(todo)
{
	然后emit update 给app.vue
}
```





动画

```
<t
```







