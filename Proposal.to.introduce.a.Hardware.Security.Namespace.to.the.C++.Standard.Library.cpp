
**Document number**: PXXXXR0  
**Date**: 2023-07-07  
**Project**: Programming Language C++  
**Reply to**: ahshabazz

# Proposal to introduce a Hardware Security Namespace to the C++ Standard Library

## Introduction

This paper proposes the addition of a new hardware security namespace to the C++ Standard Library to allow developers to better leverage hardware-level security features in a platform-independent manner. This proposal is intended as a high level architecture agnostic secure compute model because as of today both Intel, AMD, and many others have introduced various security measures in their hardware, such as Intel's Software Guard Extensions (SGX). An API in the C++ standard for these features could provide developers with the tools to ensure secure computation and data protection. 

## Motivation and Scope

Modern processors from vendors such as Intel and AMD provide various hardware-level security features, such as Intel's Software Guard Extensions (SGX). And yet currently, there is no standard way in C++ to utilize these features, and developers must rely on vendor-specific APIs and tools, leading to non-portable code.

By introducing a standard hardware security namespace, we can provide developers with a more consistent, abstracted way to use these features and improve the security of their applications without sacrificing portability.

The API call and management would be similar to the std::thread API in C++11 and later versions, because it is a suitable example of an API which uses a similar design pattern, ie.:

    Creation: A std::thread object is created by constructing an instance of the std::thread class, passing the function to be executed in a new thread as a constructor argument. This is in much the same way [[secure::enclave]] would work.

    Execution: With std::thread, the execution of std::thread starts after its creation. However with [[secure::enclave]] there is an explicit .execute() call, because the new executing context may immediately be used and reused after creation.

    Destruction: Before a std::thread object is destroyed, you must either join it (with std::thread::join()) or detach it (with std::thread::detach()), or the program will terminate. [[secure::enclave]] would employ a similar .destroy() call.

## Impact on the C++ Standard

This proposal is purely additive and does not modify any existing parts of the C++ Standard. It does not require any changes to the core language.

## Design Decisions

The proposed namespace, tentatively named `hwsec`, will initially contain an attribute to denote functions that should run in a secure context, and a class that manages secure contexts. The proposed design is similar to how `std::thread` manages threads, but separates resource acquisition and execution into separate methods to provide more control to the user.

The API signature could look as follows:

```
[[hwsec::enclave]]
void secureFunction() {
    // Code here runs in a secure enclave //
    std::cout << "Running in a secure enclave." << std::endl;
}

int main() {
    hwsec::Enclave myEnclave;

    try {
        // Create a new enclave //
        myEnclave.create();

        // Run a function inside the enclave //
        myEnclave.execute(secureFunction);

        // Destroy the enclave //
        myEnclave.destroy();
    }
    catch (const hwsec::Exception& e) {
        std::cerr << "HWSEC error: " << e.what() << std::endl;
    }

    return 0;
}
```

## Future Directions

If accepted, future extensions to the `hwsec` namespace could include additional attributes, classes, and functions to support other hardware-level security features.

## Acknowledgments

Thanks to the members of the C++ community for their valuable insights and discussions that helped shape this proposal.

## References

[To be added]
