<template>
  <div>
    <input type="text" @keyup.enter="add">
  </div>
</template>

<script>


export default {
  name: 'MyHeader',
  props:['add']
  // methods: {
  //   add(e){
  //     if(e.target.value=='') return
  //     const todoObj={
  //       id:'123',title:e.target.value,done:false
  //     }
  //     e.target.value=''
  //     console.log(todoObj)
  //   }
  // },
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>

</style>
