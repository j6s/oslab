// reader-writer example
// 2014-09-06 Ulrich Baum

import java.util.Date;
import java.util.Random;

public class ReaderWriter {
  
  // two variables shared by all threads
  static int var1 = 0;
  static int var2 = 0;

  static Random generator = new Random();   // random generator
    
  public static void main(String[] args) throws InterruptedException {
    Thread[] threads = new Thread[6]; 
    threads[0] = new Thread(new Writer("A",0,2));  // A writes even numbers
    threads[1] = new Thread(new Writer("B",1,2));  // B writes odd numbers
    threads[2] = new Thread(new Reader("c"));
    threads[3] = new Thread(new Reader("d"));
    threads[4] = new Thread(new Reader("e"));
    threads[5] = new Thread(new Reader("f"));

    long start = new Date().getTime();
    for (Thread t : threads) t.start(); // start all threads
    for (Thread t : threads) t.join();  // wait for all threads
    long end = new Date().getTime();
    System.out.printf("Done after %d ms.\n",end-start);
    
  }


  // simulate working for a given number of milliseconds
  private static void work(long msec) {
    if (msec <= 0) return;
    long start = new Date().getTime();
    while(new Date().getTime() - start < msec); // active waiting
  }


  private static class Writer implements Runnable {

    private String name;
    private int value;
    private int increment;

    public Writer(String name, int start, int increment) { 
      this.name = name; 
      this.value = start;
      this.increment = increment;
    }

    public void run() { 
      for (int i=0; i<20; i++) {
        work(generator.nextInt(20));
        System.out.printf(" %s: writing %3d, %3d\n", name, value, value);
        var1 = value; // write first variable
        work(20);     // simulate some work
        var2 = value; // write second variable
        System.out.printf(" %s: done    %3d, %3d\n", name, value, value);
        value += increment;
      }
    }

  }
  

  private static class Reader implements Runnable {

    private String name;

    public Reader(String name) { 
      this.name = name; 
    }

    public void run() { 
      for (int i=0; i<20; i++) {
        work(generator.nextInt(20));
        System.out.printf(" %s: starts reading\n", name);
        work(20);
        int v1 = var1;
        int v2 = var2;
        String mark = (v1 == v2) ? "=" : "*"; // mark different values by *
        System.out.printf("%s%s: read    %3d, %3d\n", mark, name, v1, v2);
      }
    }

  }

}  



