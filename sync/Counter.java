// race condition example
// 2014-09-06 Ulrich Baum

import java.util.Date;

public class Counter implements Runnable {

  static int counter = 0; // global counter shared by all threads

  private String name;
  private int duration;

  public Counter(String name, int duration) { 
    this.name = name; 
    this.duration = duration;
  }


  // run a thread
  public void run() { 
    // increment global counter 50 times
    for (int i=0; i<50; i++) {
      // get global counter value
      int oldval = counter;  
      System.out.printf("%s: in   %3d\n",name,oldval);
      // compute new counter value
      work(duration);  // simulate some time-consuming work in critical section
      int newval = oldval + 1;
      // set new global counter value
      counter = newval;      
      System.out.printf("%s: out  %3d\n",name,newval);
    }
  }


  // simulate working for a given number of milliseconds
  private void work(long msec) {
    if (msec <= 0) return;
    long start = new Date().getTime();
    while(new Date().getTime() - start < msec); // active waiting
  }


  public static void main(String[] args) {
    // create a thread for each command line argument
    // argument value specifies delay in critical section
    for (int i = 0; i < args.length; i++) {
      int work = Integer.parseInt(args[i]);
      String name = "" + (char)('A'+i);
      new Thread(new Counter(name, work)).start();
    }
  }

}
