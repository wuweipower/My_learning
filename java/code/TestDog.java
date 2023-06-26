
interface Animal{
    public void move();
    default void bark(){System.out.println("a");};
 }
  
 class Dog implements Animal{
   @Override
    public void move(){
       System.out.println("狗可以跑和走");
    }


 }
  
 public class TestDog{
    public static void main(String args[]){
      
       Animal b = new Dog(); // Dog 对象
  
       b.move();//执行 Dog 类的方法
       b.bark();
    }
 }
 