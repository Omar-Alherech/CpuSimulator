public class Main {

    // palindrome
    /**
     * This method determines whether or not the user inputted string
     * is a palindrome or not, whether the string is exactly the same
     * spelled backwards or foward.
     * @param test_input User input variable, check if this variable is a palindrome
     */
    public static boolean palindrome(String test_input){
        Stack<Character> letter= new Stack<Character>();
        // push the char array onto a stack, first in last out which will
        //help reverse the string
        for (int i=0;i<test_input.length();i++){
            letter.push(test_input.charAt(i));
        }
        String reverse_string= "";
        while(!letter.isEmpty()){
            reverse_string += letter.pop();
        }
        // if the reverse string is equivalent to the original input return true
        if(test_input.equals(reverse_string)){
            return true;
        }
        else{
            return false;
        }
    }
    /**
     * This method uses the logic defined based on Levenshtein distance,
     * the amount of swaps removals or replacements needed to change string a
     * to string b
     * @param a - first string
     * @param b - second string to compare
     */
    public static int editDistance(String a, String b){
        //Helper method to insert the length recursively
        return math(a,b,a.length(),b.length());

    }
    /**
     * This method uses the logic defined based on Levenshtein distance,
     * the amount of swaps removals or replacements needed to change string a
     * to string b
     *
     * @param a - first string
     * @param b - second string to compare
     * @param a_length - length of the first string
     * @param b_length - length of the second string
     */
    public static int math(String a, String b , int a_length, int b_length){
        //Two cases to make this function relatively quick, skipping the logic and
        //recieving an answer quicker
        if (a_length==0){
            return b_length;
        }
        if (b_length==0){
            return a_length;
        }
        //Check if the endings of the two strings are the same, if they are
        //computation is simpler, count through the other string
        if (a.charAt(a_length-1) == b.charAt(b_length-1))
            return math(a, b, a_length-1, b_length-1);
        //otherwise, based on the equations in the homework pdf, the minimum cost
        //is computed for insertions, removals and replacements
        return 1 + least_operations ( math(a,  b, a_length, b_length-1),
                math(a,  b, a_length-1, b_length),
                math(a,  b, a_length-1, b_length-1)
        );
    }
    /**
     * This method uses basic logic to figure out the minimum cost for the
     * strings
     *
     * @param first- first string
     * @param second- second string to compare
     * @param third - length of the first string
     */
    public static int least_operations(int first, int second, int third){
        if (first<=second && first<=third) return first;
        if (second<=first && second<=third) return second;
        else return third;
    }
    /**
     * This method uses the logic defined based on Levenshtein distance dynamically
     * to reduce redundancy,
     *
     * @param a - first string
     * @param b - second string to compare
     */
    public static int fastEditDistance(String a, String b){
        return math_dynamic(a,b, a.length(), b.length());
    }
    /**
     * This method uses the logic defined based on Levenshtein distance using
     * tables to implement dynamic programming,
     * the amount of swaps removals or replacements needed to change string a
     * to string b
     *
     * @param a - first string
     * @param b - second string to compare
     * @param a_length - length of the first string
     * @param b_length - length of the second string
     */
    public static int math_dynamic(String a, String b, int a_length, int b_length){
        int table[][] = new int[a_length+1][b_length+1];
        //Fill the recently created table from bottom to top
        for (int i=0; i<=a_length; i++)
        {
            for (int j=0; j<=b_length; j++)
            {
                //Same cases to speed up the process, if the string length is
                //0, all the characters of the other string must be inserted
                if (i==0)
                    table[i][j] = j;
                else if (j==0)
                    table[i][j] = i;
                    // if the endings are the same, ignore and continue counting
                else if (a.charAt(i-1) == b.charAt(j-1))
                    table[i][j] = table[i-1][j-1];
                    //otherwise, compute the minimum cost for
                    //insertions, removals, and replacements.
                else
                    table[i][j] = 1 + least_operations(table[i][j-1],
                            table[i-1][j],
                            table[i-1][j-1]);
            }
        }
        return table[a_length][b_length];
    }

    public static void main(String[] args) {
        // Test
//        System.out.println(fastEditDistance("abcdefg", "aqcefgj"));
//        System.out.println(editDistance("abcdefg", "aqcefgj"));
    }

}

