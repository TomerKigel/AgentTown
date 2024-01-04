<h1>Kiss - keep it simple stupid</h1>  
if it works but it is complex, it doesn't work. c++ is difficult enough, open source, and working in a team even more. So keep things simple and neat.  
  
<h1>CI is a must.</h1>
On GitHub actions, at least two actions will be set up at any given time. these actions build the project. Make sure that any commit passes both builds.  
That is because the code written in this project is cross-platform and does not rely on OS libraries. You might add code that works in linux but won't run on windows  
or visa-versa. to avoid running the code on multiple machines and to avoid errors when working with a team, just use the CI as a tool for error checking.


<h1>Convention</h1>
<h2>function and variable names </h2> 
1.) The beginning of a word should start with a small letter.  
2.) If multiple words are in the name, it should be spaced with an underscore as such: get_id()  
  
<h2>class names</h2>  
1.) The beginning of a word should start with a capital letter.  
2.) If multiple words are in the name, it should be spaced with an underscore as such: Something_Class   
  
<h2>interface names</h2>  
1.) should start with Interface_ for example: Interface_Runnable  
2.) The beginning of a word should start with a capital letter.  
3.) If multiple words are in the name, it should be spaced with an underscore as such: Interface_Graphics_Observer  
  
  
<h2>private member variables and functions</h2>    
1.) should have a following underscore as such: function_()  
  
<h2>protected member variables and functions</h2>    
1.) should have an underscore before and after function as such: _function_()  
