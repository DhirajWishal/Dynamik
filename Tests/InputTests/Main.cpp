#include "Inputs/Suppliers/KeyInputSupplier.h"
#include "Inputs/Suppliers/MouseInputSupplier.h"

class DisplayHandle :
	public DMK::Inputs::KeyInputSupplier,
	public DMK::Inputs::MouseInputSupplier {
public:
	DisplayHandle() {}
	~DisplayHandle() {}

	virtual void DMK::Inputs::KeyInputSupplier::OnInitializeSupplier() override final
	{

	}

	//virtual void DMK::Inputs::MouseInputSupplier::OnInitializeSupplier() override final
	//{
	//
	//}
};

int main()
{

}