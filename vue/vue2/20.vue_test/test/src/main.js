import Vue from 'vue'//这个用的是runtime.vue 残缺版 需要用到render
                     //使用这个 webpack打包后提交较小
import App from './App.vue'

Vue.config.productionTip = false

new Vue({
  render: h => h(App),

  // render(createElement)
  // {
  //   return createElement('h1','hello world')
  // }
  //上面是箭头函数的简写形式
  /***
   * vue.js 与 vue.runtime.xxx.js的区别
   *  1.vue.js是完整版Vue 包含核心功能与模板解析器
   *  2.和runtime版本只包含核心功能
   * 由于runtime 所有没有template配置项 需要写成我上面注释的render的形式。
   */

}).$mount('#app')
