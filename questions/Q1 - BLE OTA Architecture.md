# BLE OTA Architecture

*ADD CONTENTS HERE*

### Questions
---
You have an electronic IoT device, which uses `Bluetooth SoC` as a microcontroller. The device should support `OTA (Over The Air)` firmware updates via `BLE` communication. Your goal is to design a **reliable** OTA update architecture for the device and write a detailed, step-by-step description for the end to end process (block diagrams are welcome, no coding needed). 

```
- What are the main challenges in the process? 
```
```
- What are the security risks, when doing an OTA update, and how can you address these risks?
```

### Answers
---

##### Main Concerns and How to Address Them in a Reliable OTA Update

1. The firmware should always be recoverable from an unexpected situation, no matter what.
    1. A `Golden Image Procedure` can be used to revert the old firmware. This method requires **3 slots** in the memory. One slot for the active firmware, one slot for the downloaded firmware and one slot for the golden firmware image to be used when the active image and the downloaded image have been corrupted.
	2. A `Swap Procedure` can be used to revert the old firmware. This method requires **2 slots** and a **swap area** in the memory. One slot for the active firmware, one slot for the downloaded firmware and a small piece of memory to be used as swap area while downloading the new firmware. This way, the active firmware and the downloaded slot will be swapped after downloading the new firmware and in case of a failure of the downloaded firmware, the old active firmware will be reverted.
2. The binary to be used in the update should be `Encrypted` and `Authenticated`.
    1. Encryption ensures that even if the binary file has been stolen, they won't be able to use it on another custom board.
    2. Authentication ensures that even if someone manages to transfer a cracked and encrypted(with the correct keys) binary to the device, the bootloader will not accept to load it since it will know that it was signed by an unauthorized person.
3. `Over the Air Update Triggering Method` should be accessible even if the firmware is invalid. Imagine you have a perfect OTA Bootloader solution but the method you are using to trigger an ota update and running the bootloader is a BLE GATT Characteristic Write. A smartphone should write to this characteristic in order to trigger a firmware update but due to a problem on your firmware, it is not advertising anymore. Here are the steps to prevent that:
    1. The OTA downloader should always be a separate firmware. You can not rely on your firmware to download the new firmware and then jump to the bootloader. The firmware download and installations should be done inside the Bootloader firmware. This way, even if your firmware is broken, the bootloader can download a new one. But there is still one risk here. What if the firmware is not completely broken, it just works but you just can't trigger it to jump to the bootloader? In this case, you will lose the firmware update feauture forever. What are the options to solve this problem?
		1. Put an interaction method to pyhsically triggering a firmware update or recovery. This is the easiest and safest way but it might not be possible in every case. The work-arounds are listed below.
	    2. A periodic reset by a hardware watchdog and an insanity check of the firmware in the bootloader before running the active firmware. The active firmware can set a flag in the memory (volatile or non-volatile) during normal operation to let the bootloader know that everything is okay about the triggering method(e.g. *I am able to advertise and a smartphone is able to discover my triggering GATT characteristic*). After every hard-reset (let's say every night), the bootloader can check and reset this flag and start advertising with the **OTA Bootloader Mode** if there is a problem.
4. Memory `Read/Write/Execute/Access Protections` should be set carefully. Here are the summary about that:
    - The **Bootloader Area** should not be accessible by any kind of operation from the MCU memory or from an external programmer.
    - The **Active/Download Firmware Area** must be accessible from the **Bootloader Area** and not accessible by any kind of operation from an external programmer.
    - The `Encryption` and the `Authentication` keys must be inside the one-time-programmable area and accessible **only** by the Bootloader firmware.
	

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	