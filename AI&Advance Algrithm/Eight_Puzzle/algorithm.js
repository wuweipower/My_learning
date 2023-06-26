// 创建一个优先队列数据结构
function priority_queue() {
    var items = [];
    // 向队列尾部添加一个（或多个）新的项
    this.push = function(element){
        if(this.isEmpty()) {
            items.push(element);
        }
        else {
            var flag = false;
            for(var i = 0; i < items.length; i++){
                if(items[i].getFValue() >= element.getFValue()) {
                    items.splice(i, 0, element);
                    flag = true;
                    break;
                }
            }
            if(!flag){
                items.push(element);
            }
        }
    };
    // 移除队列的第一（即排在队列最前面的）项，并返回被移除的元素
    this.pop = function(){
        return items.shift();
    };
    // 返回队列中第一个元素——最先被添加，也将是最先被移除的元素。队列不做任何变动
    this.top = function(){
        return items[0];
    };
    // 如果队列中不包含任何元素，返回 true ，否则返回 false
    this.isEmpty = function(){
        return items.length == 0;
    };
    // 清空队列
    this.clear = function(){
        items = [];
    };
    // 返回队列包含的元素个数，与数组的 length 属性类似
    this.size = function(){
        return items.length;
    };
    this.print = function(){
        console.log(items.toString());
    };
}



const LEN = 362880;
class node
{
    state=[];
    dis;
    f;//与目标之间的差距
    constructor()
    {
        
    }
    getFValue()
    {
        return this.f;
    }
}

function getF(state,goal)//返回目前状态和目标状态之间的差距
{
    var sum=0;
    for(var i = 0; i < state.length; i++)
    {
        if(state[i]!=goal[i])
        sum+=1;
    }
    return sum;
}
var dir = [[-1,0],[0,-1],[1,0],[0,1]];

var visted = new Array(LEN).fill(false);

var start = new Array(9);
var goal = [1,2,3,8,0,4,7,6,5];
var factory = [1,1,2,6,24,120,720,5040,40320,362880];

//Cantor判重
function Cantor(str,n)
{
    result =0;
    for(var i=0;i<n;i++)
    {
        counted = 0;
        for(var j=i+1;j<n;j++)
        {
            if(str[i]>str[j])
            counted++;
        }
        result += counted*factory[n-i-1];
    }
    if(!visted[result])
    {
        visted[result]=true;
        return true;
    }
    return false;
}

function getGoal(str,goal)
{
    for(var i=0;i<str.length;i++)
    {
        if(str[i]!=goal[i])return false;
    }
    return true;
}
function BFS()//广度优先搜索
{
    var head = new node();
    for(var i=0;i<9;i++)
    {
        head.state[i]=start[i];
    }
    head.dis = 0;
    var q = new Array();
    Cantor(head.state,9);
    q.push(head);
    while(q.length!=0)
    {
        head = q.shift();
        if(getGoal(head.state,goal))
        {
            return head.dis;
        }
        var z;
        for(z=0;z<9;z++)
        {
            if(head.state[z]==0)
            break;
        }
        var x = z%3;
        var y =parseInt(z/3);
        for(var i=0;i<4;i++)
        {
            var newx = x+dir[i][0];
            var newy = y+dir[i][1];
            var nz = newx+3*newy;
            if(newx>=0 && newx<3 && newy>=0 && newy<3)
            {
                var newnode = new node();
                for(var j=0;j<9;j++)
                {
                    newnode.state[j] = head.state[j];
                }
                //Swap
                let temp = newnode.state[z];
                newnode.state[z] = newnode.state[nz];
                newnode.state[nz] = temp;
                
                newnode.dis = head.dis+1;
                if(getGoal(newnode.state,goal))
                return newnode.dis;
                if(Cantor(newnode.state,9))
                q.push(newnode);
            }
        }
    }
    return -1;
}

var ans = Infinity;
var limit = 1000;
function DFS(state,dis,num)//深度优先
{
    if(!Cantor(state,9)) return;
    if(num>=limit) return;
    Cantor(state,9);
    if(getGoal(state,goal))
    {
        if(dis<ans)
        ans = dis;
    }
    var z;
    for(z=0;z<9;z++)
    {
        if(state[z]==0)
        break;
    }
    var x = z%3;
    var y =parseInt(z/3);
    for(var i=0;i<4;i++)
    {
        var newx = x+dir[i][0];
        var newy = y+dir[i][1];
        var nz = newx+3*newy;
        if(newx>=0 && newx<3 && newy>=0 && newy<3)
        {
            var newstate = new Array(9);
            for(var j=0;j<9;j++)
            {
                newstate[j] =state[j];
            }
            //Swap
            let temp = newstate[z];
            newstate[z] = newstate[nz];
            newstate[nz] = temp;
            DFS(newstate,dis+1,num+1);
        }
    }
}
function best_first()//best first search要使用优先队列，根据F小的排序
{
    var head = new node();
    for(var i=0;i<9;i++)
    {
        head.state[i]=start[i];
    }
    head.dis = 0;
    head.f=getF(head.state,goal);
    var q = new priority_queue();
    Cantor(head.state,9);
    q.push(head);
    while(q.length!=0)
    {
        head = q.pop();
        if(getGoal(head.state,goal))
        {
            return head.dis;
        }
        var z;
        for(z=0;z<9;z++)
        {
            if(head.state[z]==0)
            break;
        }
        var x = z%3;
        var y =parseInt(z/3);
        for(var i=0;i<4;i++)
        {
            var newx = x+dir[i][0];
            var newy = y+dir[i][1];
            var nz = newx+3*newy;
            if(newx>=0 && newx<3 && newy>=0 && newy<3)
            {
                var newnode = new node();
                for(var j=0;j<9;j++)
                {
                    newnode.state[j] = head.state[j];
                }
                //Swap
                let temp = newnode.state[z];
                newnode.state[z] = newnode.state[nz];
                newnode.state[nz] = temp;

                newnode.f = getF(newnode.state,goal);
                newnode.dis = head.dis+1;

                if(getGoal(newnode.state,goal))
                return newnode.dis;

                if(Cantor(newnode.state,9))
                q.push(newnode);
            }
        }
    }
    return -1;
}


function branch()//branch and bound 
{    
    bound = Infinity; 
    var head = new node();
    for(var i=0;i<9;i++)
    {
        head.state[i]=start[i];
    }
    head.dis = 0;
    head.f=getF(head.state,goal);
    var q = new priority_queue();
    Cantor(head.state,9);
    q.push(head);
    while(q.length!=0)
    {
        head = q.pop();
        //console.log(head);
        if(head.dis>=bound)
        continue;

        if(getGoal(head.state,goal))
        {
            if(head.dis<bound)
            {
                bound = head.dis;
            }

        }
        var z;
        for(z=0;z<9;z++)
        {
            if(head.state[z]==0)
            break;
        }
        var x = z%3;
        var y =parseInt(z/3);
        for(var i=0;i<4;i++)
        {
            var newx = x+dir[i][0];
            var newy = y+dir[i][1];
            var nz = newx+3*newy;
            if(newx>=0 && newx<3 && newy>=0 && newy<3)
            {
                var newnode = new node();
                for(var j=0;j<9;j++)
                {
                    newnode.state[j] = head.state[j];
                }
                //Swap
                let temp = newnode.state[z];
                newnode.state[z] = newnode.state[nz];
                newnode.state[nz] = temp;

                newnode.f = getF(newnode.state,goal);
                newnode.dis = head.dis+1;

                if(getGoal(newnode.state,goal))
                return newnode.dis;

                if(Cantor(newnode.state,9))
                q.push(newnode);
            }
        }
    }
    if(bound!=Infinity) return bound;
    return -1;
}


// function main()
// {
//     start=[1,2,0,8,4,3,7,6,5];
//     console.log(BFS()) 
//     visted.fill(false);
// }
// main();

function getMethod()
{
    var temp = document.getElementsByName("method");
    for(var i=0;i<temp.length;i++)
    {
        if(temp[i].checked)
        {
            return temp[i].value;
        }
    }
}


function init()
{
    // var test = [1,2,3,8,0,4,7,6,5];
    // var num = parseInt(Math.random()*100)%10;
    // for(var i =0;i<num;i++)
    // {
    //     var i = parseInt(Math.random()*9)%9;
    //     var j = parseInt(Math.random()*9)%9;;
    //     //swap;;
    //     let temp = test[i];
    //     test[i] = test[j];
    //     test[j] = temp;
    // }
    // start = test;
    var data = [[6,1,5,0,2,7,3,8,4],
    [0,8,7,5,3,4,1,2,6],
    [6,3,2,4,5,7,1,0,8],
    [3,8,0,1,4,2,6,7,5],
    [4,1,5,0,3,2,7,6,8],
    [6,7,8,0,3,4,1,2,5],
    [2,1,7,4,8,3,5,0,6],
    [3,4,7,5,6,2,1,8,0],
    [3,8,1,5,0,7,6,2,4],
    [7,8,1,5,6,2,4,3,0]];
    var len = data.length;
    start =  data[Math.floor(Math.random()*len)];
    show();
}

function show()
{
    for(var i =0;i<9;i++){
        document.getElementById("pos"+i).innerHTML = start[i];
    }
}
function run()
{
    var method = getMethod();
    //init();
    var res;
    var step;
    var s = (new Date()).getTime();
    if(method=="BFS"){
        res = BFS();
        visted.fill(false);
    }
    if(method=="DFS")
    {
        DFS(start,0,0);
        res = ans;
        visted.fill(false);
    }
    if(method=="Best")
    {
        res=best_first();
        visted.fill(false);
    }
    if(method=="Branch")
    {
        res=branch();
        visted.fill(false);
    }
    var e = (new Date()).getTime();
    document.getElementById("time").innerHTML = (e-s)/1000;
    if(res!=-1 && res!=Infinity)
    {
        step = res;    
        document.getElementById("step").innerHTML = step;
        document.getElementById("result").innerHTML= "Found Goal";
    }
    else
    {
        document.getElementById("step").innerHTML = "NO";
        document.getElementById("result").innerHTML= "NOT Found Goal";
    }
    console.log(start)
}