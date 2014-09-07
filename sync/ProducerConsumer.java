// producer-consumer problem with bounded buffer
// INCOMPLETE solution with semaphore
// Ulrich Baum 2014-09-06


import java.util.Random;
import java.util.concurrent.Semaphore;

public class ProducerConsumer {
  
  private static BoundedBuffer buffer = new BoundedBuffer(4);
  private static Random generator = new Random();


  private static class BoundedBuffer {

    private String[] items;
    private int size;
    private int first = 0;  // index of first item
    private int next = 0;   // index of next item
    private int count = 0;  // number of items currently in buffer
 
    private Semaphore access; // protects read/write
    
    public BoundedBuffer(int size) {
      this.size = size;
      items = new String[size];
      access = new Semaphore(1, true);
    }
    
    public String read(String name) throws InterruptedException {
      System.out.printf("%s: wants to read\n",name);
      access.acquire();

      if (count == 0) // buffer empty
        throw new RuntimeException("buffer empty");
      String item = items[first++];
      if (first == size) first = 0;
      count--;
      System.out.printf("%s: read:  %s\n",name,item);

      access.release();
      return item;
    }

    public void write(String name, String item) throws InterruptedException {
      System.out.printf("%s: wants to write\n",name);
      access.acquire();
      
      System.out.printf("%s: write: %s\n",name,item);
      if (count == size) // buffer full
        throw new RuntimeException("buffer full");
      items[next++] = item;
      if (next == size) next = 0;
      count++;
            
      access.release();
    }
    
  }

    
  private static class Producer implements Runnable { 

    private String name;
    private int count = 0;

    public Producer(String name) { this.name = name; }

    public void run() {
      try {
        while (true) {
          sleep(generator.nextInt(200));
          String data = name + count++;
          buffer.write(name,data);
        }
      } catch (Exception e) { e.printStackTrace(); System.exit(1); };
    }  

  }
  
  
  private static class Consumer implements Runnable {    

    private String name;
    private int count = 0;
    
    public Consumer(String name) { this.name = name; }
    
    public void run() {
      try {
        while (true) {
          sleep(generator.nextInt(200));
          String data = buffer.read(name);
        }
      } catch (Exception e) { e.printStackTrace(); System.exit(1); };
    }
        
  }
  
  
  private static void sleep(long msec) {
    try { 
      Thread.sleep(msec);
    } catch(InterruptedException e) {};
  }
  
  
  public static void main(String[] args) {    
    new Thread(new Producer("A")).start();
    new Thread(new Producer("B")).start();
    new Thread(new Producer("C")).start();
    new Thread(new Producer("D")).start();
    new Thread(new Consumer("w")).start();
    new Thread(new Consumer("x")).start();
    new Thread(new Consumer("y")).start();
    new Thread(new Consumer("z")).start();
  }
  
  
}
