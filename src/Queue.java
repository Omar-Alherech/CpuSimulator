import java.util.EmptyStackException;
import java.util.LinkedList;
/**
 * The class Queue is the student's implementation of the
 * built in java class Queue. It represents a data structure
 * that allows elements to be inserted at the end of the queue,
 * and removed from the beginning, using a linked list
 *
 * @author  Omar (Porapat) Alherech
 * @version 1.0
 */
public class Queue<T> {

    // TODO
    // instance variables...
    protected LinkedList<T> list;
    private int size;
    /**
     * This method intialized the queue, setting up the linked list, and size
     * counter
     */
    public Queue() {
        // set up empty Queue
        list = new LinkedList<T>();
        size=0;
    }

    /**
     * This method sets adds and element to the back of the queue.
     */
    public void enqueue(T element) {
        size++;
        list.addLast(element);
    }
    /**
     * This method removes the object at the front of the queue, if it
     * empty an exception is thrown
     */
    public T dequeue() {
        if(isEmpty()){
            throw new EmptyStackException();
        }
        size--;
        return list.removeFirst();
    }
    /**
     * This method returns a boolean, checking if the size of the queue is 0,
     * meaning it is empty
     */
    public boolean isEmpty() {
        return (size==0);
    }
    /**
     * This method returns the top element of the queue without removing it
     */
    public T peek() {
        if (isEmpty()){
            throw new EmptyStackException();
        }
        return list.getFirst();
    }
    /**
     * This method returns the size variable, that is incremented and decremented
     * when objects enter and leave the queue.
     */
    public int length() {
        return size;
    }

}