ChatGPT Teams:

### What is Windows Sandbox?

Windows Sandbox is a lightweight desktop environment within Windows 10 and Windows 11 Pro and Enterprise editions, designed to safely run applications in isolation. Think of it as a temporary, virtual machine that is built into Windows itself, allowing you to execute software without risking your main operating system's stability, security, or integrity. Each time Windows Sandbox is initiated, it creates a brand-new, clean Windows installation environment. Once the Sandbox is closed, all the software, files, and state changes are deleted, ensuring no persistent risk or alteration to your main system.

#### Key Features of Windows Sandbox:

- **Isolation**: Windows Sandbox uses hardware-based virtualization for kernel isolation, which relies on Microsoft's hypervisor to run a separate kernel which isolates the sandbox from the host.
- **Ephemeral**: Everything in Windows Sandbox is temporary. Once you close the sandbox, all the software along with its files and state are permanently deleted.
- **Secure**: It's a secure environment to test untrusted or potentially harmful applications without affecting your host operating system.
- **Efficient**: Uses integrated kernel scheduler, smart memory management, and virtual GPU for efficient performance.

#### How to Enable Windows Sandbox:

- **Check Requirements**: Ensure your Windows 10 or Windows 11 version is Pro or Enterprise. Your hardware must also support virtualization (with AMD-V or Intel VT-x enabled in the BIOS/UEFI).
- **Enable Windows Features**: Go to Control Panel > Programs > Turn Windows features on or off. Find and enable "Windows Sandbox". Confirm and restart your computer if prompted.
- **Launch Windows Sandbox**: Once your computer restarts, you can find Windows Sandbox in the Start Menu. Click on it to launch a new sandbox session.

Windows Sandbox is particularly useful for developers, IT professionals, and general users who frequently test applications or visit potentially dangerous websites. It offers a quick and easy way to assess software without the overhead or complexity of setting up a full virtual machine through third-party software.

### How do I create a configuration file for it which disables text paste functionality?

To customize the behavior of Windows Sandbox, including disabling clipboard (text paste) functionality, you can create a configuration file (with a `.wsb` file extension) that specifies which features and behaviors you want to enable or disable. The configuration file is an XML document that Windows Sandbox will read upon starting.

#### Step 1: Create the Configuration File

- **Open Notepad** or your preferred text editor.
- **Enter the Configuration**:
  To disable clipboard functionality, you would include the `ClipboardRedirection` option in your configuration file and set it to `Disable`. Here’s an example of what the content of your configuration file might look like:

```xml
<Configuration>
  <VGpu>Disable</VGpu> <!-- Optional: Disable if you don't need GPU support -->
  <Networking>Disable</Networking> <!-- Optional: Disable if you don't need internet access -->
  <ClipboardRedirection>Disable</ClipboardRedirection> <!-- Disable clipboard redirection -->
  <!-- Add more configurations here if needed -->
</Configuration>
```

- **Save the File**:
  - Choose **File > Save As** in Notepad.
  - Select a location where you want to save the file.
  - In the **Save as type** dropdown, select **All Files**.
  - Name your file with a `.wsb` extension (for example, `NoClipboardSandbox.wsb`).
  - Click **Save**.

#### Step 2: Run Windows Sandbox with the Configuration File

- **Double-click** the `.wsb` file you created. Windows Sandbox will launch with the configurations applied, including the disabled clipboard functionality.

#### Additional Configurations

The configuration file allows for various other customizations, such as mapping folders from the host to the sandbox, setting the sandbox to use a specific amount of memory, or even running a startup script. You can add these configurations by including additional XML elements in your `.wsb` file.

For instance, to map a folder from your host machine to the sandbox, you could add the `MappedFolders` element like so:

```xml
<MappedFolders>
  <MappedFolder>
    <HostFolder>C:\Path\On\Host</HostFolder>
    <SandboxFolder>C:\Path\In\Sandbox</SandboxFolder>
    <ReadOnly>false</ReadOnly>
  </MappedFolder>
</MappedFolders>
```

Remember, after you close Windows Sandbox, all data inside it is deleted, and each time you start the sandbox with your `.wsb` configuration file, it reflects the state specified in that file. This setup is perfect for testing applications or settings in a controlled and temporary environment without affecting your primary operating system.

### How do I add read-only access to the Downloads and Documents directories?

To add read-only access to the Downloads and Documents directories in Windows Sandbox using a configuration file, you would include the `MappedFolders`

element in your `.wsb` file and specify each folder you want to map to the sandbox environment. For each folder you map, you can set whether it should be read-only or allow write access. In this case, you want to set them as read-only.

Here’s how you can modify your configuration file to include read-only access to the Downloads and Documents directories:

```xml
<Configuration>
  <VGpu>Disable</VGpu> <!-- Optional: Adjust based on your preference -->
  <Networking>Disable</Networking> <!-- Optional: Adjust based on your preference -->
  <ClipboardRedirection>Disable</ClipboardRedirection> <!-- Disable clipboard redirection -->
  <MappedFolders>
    <MappedFolder>
      <HostFolder>C:\Users\YourUsername\Downloads</HostFolder>
      <SandboxFolder>C:\Users\WDAGUtilityAccount\Downloads</SandboxFolder>
      <ReadOnly>true</ReadOnly>
    </MappedFolder>
    <MappedFolder>
      <HostFolder>C:\Users\YourUsername\Documents</HostFolder>
      <SandboxFolder>C:\Users\WDAGUtilityAccount\Documents</SandboxFolder>
      <ReadOnly>true</ReadOnly>
    </MappedFolder>
  </MappedFolders>
</Configuration>
```

#### Steps to Add Read-Only Access:

1. **Edit Your Configuration File**: Open your `.wsb` file in a text editor like Notepad.
2. **Modify the Path**: Replace `YourUsername` with your actual Windows username in the paths for the Downloads and Documents directories.
3. **Specify ReadOnly**: For each `MappedFolder`, the `<ReadOnly>` element is set to `true` to ensure read-only access.
4. **Save Your Changes**: After adding the mappings with read-only access, save your `.wsb` file.

#### Running Your Configuration:

- **Double-click** the `.wsb` file to launch Windows Sandbox with your specified configuration. You'll now have read-only access to the Downloads and Documents folders of your host system from within the sandbox.

This setup is particularly useful for safely reviewing files or executing software without the risk of altering or damaging your original files in the Downloads and Documents directories.
