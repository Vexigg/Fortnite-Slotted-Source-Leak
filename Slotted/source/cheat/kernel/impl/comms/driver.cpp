#ifndef DRIVER_CPP
#define DRIVER_CPP

#include "driver.hpp"

auto driver::comms::send_cmd(
	void* data,
	requests code) -> bool
{
	if (!data || !code)
		return false;

	IO_STATUS_BLOCK block;
	invoke_data request{ 0 };

	request.unique = requests::invoke_unique;
	request.data = data;
	request.code = code;

	auto result =
		direct_device_control(
			this->m_handle,
			nullptr,
			nullptr,
			nullptr,
			&block,
			0,
			&request,
			sizeof(request),
			&request,
			sizeof(request));

	return result;
}



auto driver::comms::initialize_handle() -> bool
{
	this->m_handle = CreateFileA(DEVICE, GENERIC_READ, 0, 0, 3, 0x00000080, 0);
	if (this->m_handle != INVALID_HANDLE_VALUE)
	{
		this->m_pid = GetCurrentProcessId();
		return true;
	}

	return false;
}

auto driver::comms::attach(
	int a_pid) -> bool
{
	if (!a_pid)
		return false;

	this->m_pid = a_pid;

	return true;
}

auto driver::comms::get_image_base(
	const char* module_name) -> const std::uintptr_t
{
	base_invoke data{ 0 };

	data.pid = this->m_pid;
	data.handle = 0;
	data.name = module_name;

	this->send_cmd(
		&data,
		invoke_base);

	this->image_base =
		data.handle;

	return data.handle;
}


auto driver::comms::write_virtual(
	const std::uintptr_t address,
	void* buffer,
	const std::size_t size) -> bool
{
	write_invoke data{ 0 };

	data.pid = this->m_pid;
	data.address = address;
	data.buffer = buffer;
	data.size = size;

	auto result =
		this->send_cmd(
			&data,
			invoke_write);

	return result;
}

auto driver::comms::read_virtual
(
	const std::uintptr_t address,
	void* buffer,
	const std::size_t size) -> bool
{
	read_invoke data{ 0 };

	data.pid = this->m_pid;
	data.address = address;
	data.buffer = buffer;
	data.size = size;

	auto result =
		this->send_cmd(
			&data,
			invoke_read);

	return result;
}

auto driver::comms::read_kernel(
	const uintptr_t address,
	void* buffer,
	const size_t size,
	const uint32_t memory_type) -> bool
{

	read_kernel_invoke data{ 0 };

	data.address = address;
	data.buffer = buffer;
	data.size = size;
	data.memory_type = memory_type;

	auto result =
		this->send_cmd(
			&data,
			invoke_read_kernel
		);

	return result;
}

auto driver::comms::translate_address(
	std::uintptr_t virtual_address,
	std::uintptr_t directory_base) -> const std::uintptr_t
{
	translate_invoke data{ 0 };

	data.virtual_address = virtual_address;
	data.directory_base = directory_base;
	data.physical_address = nullptr;

	this->send_cmd(
		&data,
		invoke_translate
	);

	return reinterpret_cast<std::uintptr_t>(data.physical_address);
}

auto driver::comms::get_dtb(
	std::uint32_t pid) -> const std::uintptr_t
{
	dtb_invoke data{ 0 };

	data.pid = pid;
	data.dtb = 0;

	auto result =
		this->send_cmd(
			&data,
			invoke_dtb
		);

	return data.dtb;
}

auto driver::comms::get_cr3(
	std::uintptr_t base_address) -> bool
{
	auto ntdll_address = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("ntdll.dll"));
	if (!ntdll_address) {
		return false;
	}

	auto current_dtb = this->get_dtb(GetCurrentProcessId());
	if (!current_dtb) {
		return false;
	}

	auto nt_dll_physical = this->translate_address(
		ntdll_address,
		current_dtb
	);

	for (std::uintptr_t i = 0; i != 0x50000000; i++)
	{
		std::uintptr_t dtb = i << 12;

		if (dtb == current_dtb)
			continue;

		auto phys_address = this->translate_address(
			ntdll_address,
			dtb
		);

		if (!phys_address)
			continue;

		if (phys_address == nt_dll_physical)
		{
			this->dtb = dtb;

			const auto bytes = this->read<char>(base_address);
			if (bytes == 0x4D)
			{
				// you can remove this just to show you 
				//std::printf( " [dtb] -> 0x%p\n", dtb );

				this->dtb = dtb;
				break;
			}
		}
	}

	FreeLibrary(reinterpret_cast<HMODULE>(ntdll_address));
	return true;
}


#endif // ! DRIVER_CPP
