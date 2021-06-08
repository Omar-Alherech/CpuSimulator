import java.util.EmptyStackException;
import java.util.LinkedList;
/**
 * The class Stack is a students implementation of a
 * build in java class stack using a linked list, it is based
 * on Last in first out logic, with two main processes push and pop.
 *
 * @author  Omar (Porapat) Alherech
 * @version 1.0
 */
public class Stack<T> {
    // instance variables../
    protected LinkedList<T> list;
    protected int top;
    /**
     * This method initializes the queue, and set the top variable to -1,
     * making it simpler to check if the stack is empty or not.
     */
    public Stack() {
        top = -1;
        list = new LinkedList<T>();
    }
    /**
     * This method adds and element to the bottom of the stack, incrementing the counter
     */
    public void push(T element) {
        list.addFirst(element);
        top++;
    }
    /**
     * This method pulls an element off the top of the stack, decrementing the counter
     */
    public T pop() {
        if(isEmpty()){
            throw new EmptyStackException();
        }
        top--;
        return list.removeFirst();
    }
    /**
     * This method returns the topmost element on the stack without removing
     * the element.
     */
    public T peek() {
        if(isEmpty()){
            throw new EmptyStackException();
        }
        return list.getFirst();
    }
    /**
     * This method checks the value of the top variable and returns a
     * boolean detailing if the stack is empty or not.
     */
    public boolean isEmpty() {
        return (top == -1);
    }
    /**
     * This method returns the top variable, adding one to signify
     * the size.
     */
    public int length() {
        if(isEmpty()){
            throw new EmptyStackException();
        }
        else{
            return top+1;
        }
    }

}