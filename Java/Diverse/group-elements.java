import java.util.LinkedList;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * Given an array of `n` numbers, divide this array in groups
 * such that the sum of a group g is divisible by n.
 * 
 * Note than a group can be eliminated. If the eliminated group contains 2 elements,
 * the next group after it must have the sum divisible with n - 2 
 */

/*
Example:
1)
n = 6 
arr = {4, 10, 3, 9, 2, 3}

A possible solution:
10 3 9 2 ( 24 % 6 = 0) 
4 ( 4 % 2 = 0)
3 ( 3 % 1 = 0)

2)
n = 10
arr = {4, 10, 3, 9, 2, 3, 7, 3, 5, 53}

A possible solution
[10]
[4, 3, 9, 2]
[3, 7]
[3]
[5, 53]

*/


public class Test { 

    class Pair {
        int index, value;
        Pair(int _i, int _v) {
            this.index = _i;
            this.value = _v;
        }
    }

    public <T extends Integer> Pair contains(final List<T> array, final T v) {
        int index = 0;
        for(final T e: array) {
            if(e == v) 
                return new Pair(index, e);
            index++;
        }

        return null;
    }

    public List<Integer> generateSum(List<Integer> arr) {
        List<Integer> temp = new ArrayList<>();
        temp.add(arr.get(0));

        for(int i = 1; i < arr.size(); i++)
            temp.add(temp.get(i - 1) + arr.get(i));
        
        return temp;
    }

    public void solve(List<Integer> arr) {
        Integer size = arr.size();
        int start = -1;
        int end = -1;
        int zero = -1;
        List<Integer> sum;
        List<Integer> remaining = new LinkedList<>();
        Boolean found;
        List<List<Integer>> groups = new ArrayList<List<Integer>>();

        while(arr.size() != 0) {
            sum = generateSum(arr);
            Integer currentSize = sum.size();
            found = false;

            for(int i = 0; i < currentSize; i++) {
                int rest = sum.get(i) % currentSize;
                Pair p = contains(remaining, rest);

                if(rest == 0) {
                    zero = i;
                    found = true;
                    break;
                }

                if(p != null && found == false) {
                    start = p.index; 
                    end = i;
                    found = true;
                }
                remaining.add(rest);
            }

            if(found == false) {
                System.out.println("stop");
                return;
            }

            start++;
            if(zero != -1) {
                start = 0;
                end = zero;
            }
            List<Integer> p = new ArrayList<Integer>(size);
            for(int i = start ; i <= end; i++)
                p.add(arr.get(i));
            groups.add(p);
            System.out.println(p);
            arr.subList(start, end + 1).clear();
            remaining.clear();
        } 

        groups.forEach(System.out::println);
    }

    public static void main(String[] args) {
        List<Integer> arr = new LinkedList<Integer>(Arrays.asList(4, 10, 3, 2, 3, 7, 3, 5, 11,53,11,30));
        Test t = new Test();
        t.solve(arr);  
    }
}
