// Semaphor-Übung
// 2014-09-06 Ulrich Baum

import java.util.concurrent.Semaphore;

public class SemaTest {
    
  static Semaphore x = new Semaphore(1, true);
  static Semaphore y = new Semaphore(1, true);

    
  public static void main(String[] args) throws InterruptedException {
    Thread t1 = new Thread(new A());
    Thread t2 = new Thread(new B());
    t1.start(); t2.start();
    t1.join();  t2.join();
    System.out.println();
  }


  private static void sleep(long msec) {
    try { 
      Thread.sleep(msec);
    } catch(InterruptedException e) {};
  }
  

  private static class A implements Runnable {
    public void run() { 
      
      for (int i = 0; i<5; i++) {
          
        System.out.print("a");
                  
      }
      
    }
  }

  private static class B implements Runnable {
    public void run() { 
      
      for (int i = 0; i<5; i++) {
        
        System.out.print("b");
          
      }
      
    }
  }
  
}  



