<template>
    <!-- 组建的结构 -->
    <div class="demo">
        <h1>{{ name }}</h1>
    </div>

</template>

<script>
    export default{
        name:'school',
        data()
        {
            return {
                name:'school',
            }
        }
    }
</script>

<style>
    .demo{
        background-color: orange;
    }
</style>