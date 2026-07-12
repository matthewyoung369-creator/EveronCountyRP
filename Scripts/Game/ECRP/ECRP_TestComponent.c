[ComponentEditorProps(
	category: "Everon County RP",
	description: "Runs a basic ECRP startup test"
)]
class ECRP_TestComponentClass : ScriptComponentClass
{
}

class ECRP_TestComponent : ScriptComponent
{
	override void OnPostInit(IEntity owner)
	{
		super.OnPostInit(owner);

		Print("ECRP: Test component started!", LogLevel.NORMAL);
	}
}