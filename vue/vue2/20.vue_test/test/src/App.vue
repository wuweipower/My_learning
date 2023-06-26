<template>
<div>
  <MyHeader :add="addTodo"></MyHeader>
  <MyList :todos="todos" :checkTodo="checkTodo"></MyList>
  <MyFooter></MyFooter>
</div>
</template>

<script>
import MyHeader from './components/MyHeader.vue'
import MyFooter from './components/MyFooter.vue';
import MyList from './components/MyList.vue';


export default {
  name: 'App',
  components: {
   MyHeader,MyFooter,MyList
  },
  data()
  {
    return {
      todos:[
        {id:'001',title:'A',done:true},
        {id:'002',title:'B',done:false},
        {id:'003',title:'C',done:true},
      ]
    }
    
  },
  methods:{
    addTodo(e)
    {
      if(e.target.value=='') return
      const todoObj={
        id:'123',title:e.target.value,done:false
      }
      e.target.value=''
      this.todos.unshift(todoObj)
    },
    checkTodo(id)
    {
      this.todos.forEach((todo)=>{
        if(todo.id===id) todo.done = !todo.done
      })
    }
  }
}
</script>

<style>
 
</style>
