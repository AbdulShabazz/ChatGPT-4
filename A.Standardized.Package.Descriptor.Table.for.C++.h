
Document number: PXXXXR0
Date: 2023-07-07
Project: Programming Language C++, Library Evolution Working Group
Reply-to: ahshabazz

# Standardized Package Descriptor table for C++

## Introduction

There has been a significant amount of discussion in the C++ community about the need for a standardized package manager. One of the persistent challenges in the C++ ecosystem is the diversity of package management solutions but the lack of a standardized way to describe the metadata of a library or package. Each package manager requires its own specific configuration file or filess, making it harder for library authors to ensure their work is easily accessible and usable across different environments. This proposal suggests introducing a standardized package descriptor table to simplify third party library distribution, integration, support, and usage.

A Standardized Package Descriptor Table encompasses defining a standard format for describing a package, including its dependencies, build options, platforms, etc., and would allow all package managers to use that information in a consistent manner. This would also make it easier for libraries to provide the necessary information to be used with any package manager.

There are several third-party package managers available, such as Conan, vcpkg, and CMake's FetchContent module. These tools have various capabilities and focus on different aspects of package management, but none of them is an official part of the C++ standard.

For sound and music programming and audio processing, in general, you would typically need to use a third-party library. Some libraries that have been used for this purpose include:

    SFML (Simple and Fast Multimedia Library)
    SDL (Simple DirectMedia Layer)
    PortAudio
    RtAudio
    OpenAL 

## The Problem

One of the challenges in creating a standardized package manager for C++ is the complexity of the language and its ecosystem. C++ supports many platforms and compilers, and has a vast number of libraries, each with their own configuration and build requirements. It is understandable these factors make it difficult to create a one-size-fits-all solution. Currently, every package manager (like Conan, vcpkg, etc.) has its own way of describing these things, which means that library authors need to provide this information in multiple formats if they want their libraries to be easily used with different package managers. For example, a library might need a `conanfile.py` for Conan, a `CONTROL` or `vcpkg.json` file for vcpkg, and so on. 

However a standardized package descriptor would be a consistent way to describe a package/library's metadata such as its name, version, dependencies, supported platforms, build system requirements, configuration options, and so on et al. 

With a standardized package descriptor, library authors could provide this information just once, in a single, standard format. Then, any package manager that complies with the standard could read this information and handle the library appropriately.

For instance, this descriptor could specify what other libraries are needed to build and use the library in question. If these dependencies are also using the standardized package descriptor, the third party package manager can automatically fetch and build these as needed. This simplifies the process for both library authors and end-users, who can use any package manager they so desire, confident it will be able to handle any library that uses the standard descriptor.

For sound libraries specifically, they often have dependencies on lower-level libraries for things like accessing audio hardware or performing complex mathematical operations. Being able to specify these dependencies in a standard way makes it easier for users to build and use these libraries, as the package manager can automatically resolve and install the necessary dependencies.

Creating such a standard would be a significant undertaking I'd imagine and would require agreement from many different parties. The C++ community is so diverse and includes many different tools, platforms, and use cases, so finding a one-size-fits-all solution will be challenging. It would also likely require existing package managers to be updated or rewritten to support the new standard, which could be a significant amount of work. Nevertheless, the benefits in terms of simplicity and interoperability could be substantial.

## Proposed Solution

We propose a standardized package descriptor that provides a universal way to define package metadata within the C++ ecosystem. This descriptor table would contain essential details such as:

- Package name and version.
- vendor-specific license information, terms, privacy, and or contact information.
- List of package dependencies and their versions.
- Supported platforms and compilers.
- Build system requirements.
- Configuration options.

A standardized package descriptor table would enable library authors to define their own package metadata just once in a universally understood way. This descriptor can then be used by any compliant package manager to manage the library appropriately.

## Benefits

1. **Simplicity**: Library authors would only need to maintain one descriptor file, simplifying the process of library distribution.

2. **Interoperability**: Different package managers could use the same descriptor, increasing interoperability across different environments.

3. **Consistency**: A standardized descriptor would ensure consistent handling of libraries across different package managers, reducing the potential for errors and inconsistencies.

## Conclusion

The C++ ecosystem would significantly benefit from a standardized package descriptor table, simplifying third party library distribution, integration, support, and management, for usage across various package managers. We propose that a working group be formed to further investigate this concept, determine the specifications for the standardized package descriptor, and consider how best to integrate this into the upcoming C++ standard.

Regards, 
Abdul S.
