<template>
  <li>
    <label>
      <input type="checkbox" :checked="todo.done" @change="checkTodo(todo.id)">
      <span>{{ todo.title }}</span>

    </label>
    <button class="btn" style="display: none;" @click="handleDelete(todo.id)">delete</button>
  </li>
</template>

<script>
export default {
  name: 'MyItem',
  props:['todo','checkTodo'],
  methods:{
    handleCheck(id)
    {
      this.checkTodo(id);
    },
    handleDelete(id)
    {
      if(confirm('are you sure'))
      {
        console.log(id)
      }
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
li:hover{
  background-color: gray;
}
li:hover button{
  display: block;
}
</style>
