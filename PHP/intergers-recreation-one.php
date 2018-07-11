<?php

  // Link to the task : http://www.codewars.com/kata/integers-recreation-one/solutions?show-solutions=1

    function checkSum ($item) {
        
        $sum = 0;

        // Loop through its divisors and get the sum of their squared
        // floor(sqrt($item)) -  make this more efficient
        for($i = 1; $i <= floor(sqrt($item));$i++) {

            // Check the divisor
            if($item % $i == 0) {
                
                // Then we add to the sum
                $sum += pow($i,2);

                // Check if we can find another divisor
                $another = $item / $i;

                if($another != $i) {

                    // If we found another one, we'll add it as well
                    $sum += pow($another,2);
                }

            }


        }

        
        return  $sum;

    } 

    function listSquared($m, $n) {
        
        // See if we found or not at least one result
        $found = 0;

        $output  = array();

        for($i = $m ; $i <= $n; $i++) {
            
            // if(($theSum = checkSum($i)) !== FALSE) {
            //     $output [] = array($i, $theSum);
            // }
            $theSum = checkSum($i);
            $root = sqrt($theSum);    
            if($root == floor($root)) {
                $output [] = array($i, $theSum);
            }    
        
        }

        return $output;

    }


    $res = listSquared(1,250);
    print_r($res);

    // Other examples

    class IntegerRecreationTestCases extends TestCase {
        private function revTest($actual, $expected) {
            $this->assertEquals($expected, $actual);
        }
        public function testBasics() {
            $this->revTest(listSquared(1, 250), [[1, 1], [42, 2500], [246, 84100]]);
            $this->revTest(listSquared(42, 250), [[42, 2500], [246, 84100]]);
            $this->revTest(listSquared(250, 500), [[287, 84100]]);
            $this->revTest(listSquared(300, 600), []);
        }
    }
   

   
