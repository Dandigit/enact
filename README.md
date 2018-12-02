<p align="center">
<img src="./docs/img/enact-logo-text.png" alt="Enact logo" width="60%" height="60%"></img><br>
Enact is a new programming language that's not designed to be unique or groundbreaking. Instead, Enact takes already 
established technologies and paradigms and just makes them <strong>nicer</strong>.
</p>

## Example
```
// FizzBuzz in Enact

fun main():
    each i in 1..20:
        given i % 3 == 0, i % 5 == 0:
            when true, true:
                print("FizzBuzz")
            when true, false:
                print("Fizz")
            when false, true:
                print("Buzz")
            else:
                print(i)
        end
    end
end
```

## Goals
Enact is designed to make programming easier through high-level but high-performance constructs to deal with **data**. Be it 
selection of data, iteration of data, or sorting of data, Enact will let you manipulate data easily. 
