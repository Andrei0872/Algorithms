<?php
function tribonacci($signature, $n) {
  // if $n == 0, we return an empty array
  if($n == 0) {
  return $c = array();
}

  //case which $n is less than 3
   if($n < 3) {

  return $a = array_slice($signature,0,$n);
  } else {
 
   //the other case

  //we must add the sum of the last 3 elements
  for($i=3;$i<=$n-1;$i++) {

  //we push the sum of the last 3
  array_push($signature,(float)($signature[$i-1] + $signature[$i-2] + $signature[$i-3]));
} 
  


return $b = array_slice($signature,0);

}
    

}


class MyTestCases extends TestCase {
   
  public function testBasics() {
    $this->assertEquals(tribonacci([1,1,1],10),[1,1,1,3,5,9,17,31,57,105]);
    $this->assertEquals(tribonacci([0,0,1],10),[0,0,1,1,2,4,7,13,24,44]);
    $this->assertEquals(tribonacci([0,1,1],10),[0,1,1,2,4,7,13,24,44,81]);
    $this->assertEquals(tribonacci([1,0,0],10),[1,0,0,1,1,2,4,7,13,24]);
    $this->assertEquals(tribonacci([0,0,0],10),[0,0,0,0,0,0,0,0,0,0]);
    $this->assertEquals(tribonacci([1,2,3],10),[1,2,3,6,11,20,37,68,125,230]);
    $this->assertEquals(tribonacci([3,2,1],10),[3,2,1,6,9,16,31,56,103,190]);
    $this->assertEquals(tribonacci([1,1,1],1),[1]);
    $this->assertEquals(tribonacci([300,200,100],0),[]);
    $this->assertEquals(tribonacci([0.5,0.5,0.5],30),[0.5,0.5,0.5,1.5,2.5,4.5,8.5,15.5,28.5,52.5,96.5,177.5,326.5,600.5,1104.5,2031.5,3736.5,6872.5,12640.5,23249.5,42762.5,78652.5,144664.5,266079.5,489396.5,900140.5,1655616.5,3045153.5,5600910.5,10301680.5]);
  }
  
}
