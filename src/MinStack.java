/**
 * The class Stack is a students implementation of a
 * build in java class stack using a linked list, it is based
 * on Last in first out logic, with two main processes push and pop.
 *
 * @author  Omar (Porapat) Alherech
 * @version 1.0
 */
public class MinStack<T extends Comparable<T>> extends Stack<T> {
    // instance variables...
    Stack<T> minstack;
    private int mintop;
    /**
     * This method initializes the Minstack variables, using the
     * previously defined stack.
     */
    public MinStack() {
        super();
        //same logic for the size
        mintop = -1;
        minstack = new Stack<>();
    }
    /**
     * This method is overrided, as with every push, the minimum value must be traced
     * in order to remain updated, otherwise the high level logic is the same
     */
    @Override
    public void push(T element) {
        T prev;
        if(isEmpty()){
            super.push(element);
            minstack.push(element);
        }
        else{
            super.push(element);
            prev = minstack.peek();
            if(element.compareTo(prev)==-1){
                minstack.push(element);
            }
            else{
                minstack.push(prev);
            }
        }
    }
    /**
     * This method is overrided, as with every pop, the minimum value must be traced
     * in order to remain updated, otherwise the high level logic is the same
     */
    @Override
    public T pop() {
        T x = super.pop();
        minstack.pop();
        return x;
    }

    /**
     * This method is returns the value at the top of the minstack, the most recent minimum.
     */
    public T getMin() {
        // return the minimum element of the stack in O(1) time
        T val = minstack.peek();
        return val;
    }

}