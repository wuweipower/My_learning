<template>
<div>
  
</div>
</template>

<script>
export default {
  name: 'MyFooter',

}

</script>

total()
{
  this.todos.reduce(
    (pre,curr)=>{
      return pre+1
    },0
  )
}
<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>

</style>
