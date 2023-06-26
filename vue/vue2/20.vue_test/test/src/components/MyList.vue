<template>
  <div>
    <MyItem v-for="todoObj in todos" :key="todoObj.id" :todo="todoObj"
    :checkTodo="checkTodo"></MyItem>
  </div>
</template>

<script>

import MyItem from './MyItem.vue';

export default {
  name: 'MyList',
  components:{
    MyItem,
  },
  props:['todos','checkTodo']
}
  
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>

</style>
