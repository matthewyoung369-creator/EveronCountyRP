// Native contextual action exposed by the Job Board's ActionsManagerComponent.
class ECRP_AcceptDeliveryDriverAction : ScriptedUserAction
{
	protected static const float MAXIMUM_DISTANCE = 3.0;
	protected static const string DELIVERY_DRIVER_JOB_ID = "delivery_driver";

	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		ChimeraCharacter character = ChimeraCharacter.Cast(pUserEntity);

		if (!character)
		{
			Print(
				"ECRP: Delivery Driver job assignment failed: user is not a character.",
				LogLevel.ERROR
			);
			return;
		}

		ECRP_PlayerJobComponent jobComponent =
			ECRP_PlayerJobComponent.Cast(
				character.FindComponent(ECRP_PlayerJobComponent)
			);

		if (!jobComponent)
		{
			Print(
				"ECRP: Delivery Driver job assignment failed: player job component is missing.",
				LogLevel.ERROR
			);
			return;
		}

		if (jobComponent.HasActiveJob())
		{
			Print(
				"ECRP: Player already has an active job.",
				LogLevel.NORMAL
			);
			return;
		}

		if (!jobComponent.AssignJob(DELIVERY_DRIVER_JOB_ID))
		{
			Print(
				"ECRP: Delivery Driver job assignment failed.",
				LogLevel.ERROR
			);
			return;
		}

		Print(
			"ECRP: Delivery Driver job assigned.",
			LogLevel.NORMAL
		);
	}

	override bool CanBeShownScript(IEntity user)
	{
		return IsUserInRange(user);
	}

	override bool CanBePerformedScript(IEntity user)
	{
		return IsUserInRange(user);
	}

	override bool HasLocalEffectOnlyScript()
	{
		return true;
	}

	override bool GetActionNameScript(out string outName)
	{
		outName = "Accept Delivery Driver Job";
		return true;
	}

	protected bool IsUserInRange(IEntity user)
	{
		IEntity owner = GetOwner();

		if (!owner || !user)
			return false;

		return vector.Distance(
			owner.GetOrigin(),
			user.GetOrigin()
		) <= MAXIMUM_DISTANCE;
	}
}
